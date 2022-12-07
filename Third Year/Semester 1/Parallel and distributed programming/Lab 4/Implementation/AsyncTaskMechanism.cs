using System.Net;
using System.Net.Sockets;
using System.Text;
using A4.Model;
using A4.Utils;

namespace A4.Implementation;

public class AsyncTaskMechanism
{
    private static List<string> HOSTS;
    private static List<Task> TASKS;

    public static void Run(List<string> hostnames)
    {
        HOSTS = hostnames;
        TASKS = new List<Task>();
        for (var i = 0; i < HOSTS.Count; i++)
        {
            TASKS.Add(Task.Factory.StartNew(DoStart, i));
        }
        Task.WaitAll(TASKS.ToArray());
    }

    private static void DoStart(object idObject)
    {
        var id = (int)idObject;
        StartClient(HOSTS[id], id);
    }

    private static async void StartClient(string host, int id)
    {
        // establish the remote endpoint of the server
        var ipHostInfo = Dns.GetHostEntry(host.Split('/')[0]);
        var ipAddress = ipHostInfo.AddressList[0];
        var remoteEndpoint = new IPEndPoint(ipAddress, HttpUtils.HTTP_PORT);
        
        // create a TCP/IP socket
        var client = new Socket(ipAddress.AddressFamily, SocketType.Stream, ProtocolType.Tcp);
        
        // create a state for the connection information
        var state = new StateObject
        {
            socket = client,
            hostname = host.Split('/')[0],
            endpointPath = host.Contains("/") ? host.Substring(host.IndexOf("/")) : "/",
            remoteEndPoint = remoteEndpoint,
            clientID = id
        };
        
        // connect to the remote endpoint
        await Connect(state);
        
        // request data from the server
        await Send(state, HttpUtils.GetRequestString(state.hostname, state.endpointPath));
        
        // receive the response from the server
        await Receive(state);
        
        // write the response details to the console
        Console.WriteLine(state.responseContent);
        
        // release the socket
        client.Shutdown(SocketShutdown.Both);
        client.Close();
    }

    private static async Task Connect(StateObject state)
    {
        state.socket.BeginConnect(state.remoteEndPoint, ConnectCallback, state);
        await Task.FromResult<object>(state.connectDone.WaitOne());
    }
    
    private static void ConnectCallback(IAsyncResult ar)
    {
        // retrieve the details from the connection information wrapper
        var state = (StateObject)ar.AsyncState;
        var clientSocket = state.socket;
        var clientID = state.clientID;
        var hostname = state.hostname;
        
        //complete the connection
        clientSocket.EndConnect(ar);
        
        Console.WriteLine("{0}) Socket connected to {1} ({2})", clientID, hostname, clientSocket.RemoteEndPoint);
        
        // signal that the connection has been made
        state.connectDone.Set();
    }
    
    private static async Task Send(StateObject state, string data)
    {
        // convert the string data to byte data using ASCII encoding
        var byteData = Encoding.ASCII.GetBytes(data);
        
        // begin sending the data to the server
        state.socket.BeginSend(byteData, 0, byteData.Length, 0, SendCallback, state);
        await Task.FromResult<object>(state.sendDone.WaitOne());
    }
    
    private static void SendCallback(IAsyncResult ar)
    {
        // retrieve the details from the connection information wrapper
        var state = (StateObject)ar.AsyncState;
        var clientSocket = state.socket;
        var clientID = state.clientID;
        
        // complete sending the data to the server
        var bytesSent = clientSocket.EndSend(ar);
        Console.WriteLine("{0}) Sent {1} bytes to the server.", clientID, bytesSent);
        
        // signal that all bytes have been sent
        state.sendDone.Set();
    }
    
    private static async Task Receive(StateObject state)
    {
        // begin receiving the data from the server
        state.socket.BeginReceive(state.receiveBuffer, 0, StateObject.BUFFER_SIZE, 0, ReceiveCallback, state);
        await Task.FromResult<object>(state.receiveDone.WaitOne());
    }
    
    private static void ReceiveCallback(IAsyncResult ar)
    {
        // retrieve the details from the connection information wrapper
        var state = (StateObject)ar.AsyncState;
        var clientSocket = state.socket;

        try
        {
            // read data from the server
            var bytesRead = clientSocket.EndReceive(ar);
            
            // get from the buffer, a number of characters <= buffer size, and store them in the response content
            state.responseContent.Append(Encoding.ASCII.GetString(state.receiveBuffer, 0, bytesRead));
            
            // if the response header has not been fully obtained, get the next chunk of data
            if (!HttpUtils.ResponseHeaderFullyObtained(state.responseContent.ToString()))
            {
                clientSocket.BeginReceive(state.receiveBuffer, 0, StateObject.BUFFER_SIZE, 0, ReceiveCallback, state);
            }
            else
            {
                // header has been fully obtained
                // get the body
                var responseBody = HttpUtils.GetResponseBody(state.responseContent.ToString());
                
                // the custom header parser is being used to check if the data received so far has the length specified in the response headers
                if (responseBody.Length < HttpUtils.GetContentLength(state.responseContent.ToString()))
                {
                    // if it isn't, then more data is to be retrieved
                    clientSocket.BeginReceive(state.receiveBuffer, 0, StateObject.BUFFER_SIZE, 0, ReceiveCallback, state);
                }
                else
                {
                    // all data has been received
                    // signal that all bytes have been received
                    state.receiveDone.Set();
                }
            }
        } catch (Exception e)
        {
            Console.WriteLine(e.ToString());
        }
    }
}