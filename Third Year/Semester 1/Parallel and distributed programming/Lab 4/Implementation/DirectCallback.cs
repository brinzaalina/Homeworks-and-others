using System.Net;
using System.Net.Sockets;
using System.Text;
using A4.Model;
using A4.Utils;

namespace A4.Implementation;

public class DirectCallback
{
    private static List<string> HOSTS;

    public static void Run(List<string> hostnames)
    {
        HOSTS = hostnames;
        for (var i = 0; i < HOSTS.Count; i++)
        {
            DoStart(i);
        }
    }

    private static void DoStart(object idObject)
    {
        var id = (int)idObject;
        StartClient(HOSTS[id], id);
        Thread.Sleep(2000);
    }

    private static void StartClient(string host, int id)
    {
        // establish the remote endpoint of the server
        var hostInfo = Dns.GetHostEntry(host.Split('/')[0]);
        var ipAddress = hostInfo.AddressList[0];
        var remoteEndpoint = new IPEndPoint(ipAddress, HttpUtils.HTTP_PORT);
        
        // create the TCP/IP socket
        var client = new Socket(ipAddress.AddressFamily, SocketType.Stream, ProtocolType.Tcp);
        
        // create a state containing the connection information
        var state = new StateObject
        {
            socket = client,
            hostname = host.Split('/')[0],
            endpointPath = host.Contains("/") ? host.Substring(host.IndexOf("/")) : "/",
            remoteEndPoint = remoteEndpoint,
            clientID = id
        };
        
        // connect to the remote endpoint
        state.socket.BeginConnect(state.remoteEndPoint, OnConnect, state);
    }

    private static void OnConnect(IAsyncResult ar)
    {
        // retrieve the details from the connection information wrapper
        var state = (StateObject)ar.AsyncState;
        var clientSocket = state.socket;
        var clientID = state.clientID;
        var hostname = state.hostname;
        
        // complete the connection
        clientSocket.EndConnect(ar);
        Console.WriteLine("{0}) Socket connected to {1} ({2})", clientID, hostname, clientSocket.RemoteEndPoint);
        
        // convert the string data to byte data using ASCII encoding
        var byteData = Encoding.ASCII.GetBytes(HttpUtils.GetRequestString(state.hostname, state.endpointPath));
        
        // begin sending the data to the server
        state.socket.BeginSend(byteData, 0, byteData.Length, 0, OnSend, state);
    }

    private static void OnSend(IAsyncResult ar)
    {
        var state = (StateObject)ar.AsyncState;
        var clientSocket = state.socket;
        var clientID = state.clientID;
        
        // complete sending the data to the server
        var bytesSent = clientSocket.EndSend(ar);
        Console.WriteLine("{0}) Sent {1} bytes to server.", clientID, bytesSent);
        
        // begin receiving the response from the server
        state.socket.BeginReceive(state.receiveBuffer, 0, StateObject.BUFFER_SIZE, 0, OnReceive, state);
    }

    private static void OnReceive(IAsyncResult ar)
    {
        // retrieve the details from the connection information wrapper
        var state = (StateObject)ar.AsyncState;
        var clientSocket = state.socket;
        var clientID = state.clientID;

        try
        {
            // read data from the server
            var bytesRead = clientSocket.EndReceive(ar);
            
            // get from the buffer, a number of characters <= the buffer size, and store it in the responseContent
            state.responseContent.Append(Encoding.ASCII.GetString(state.receiveBuffer, 0, bytesRead));
            
            // if the response header has not been fully obtained, get the next chunk of data
            if (!HttpUtils.ResponseHeaderFullyObtained(state.responseContent.ToString()))
            {
                clientSocket.BeginReceive(state.receiveBuffer, 0, StateObject.BUFFER_SIZE, 0, OnReceive, state);
            }
            else
            {
                // header fully obtained, get the body
                var responseBody = HttpUtils.GetResponseBody(state.responseContent.ToString());
                
                // the custom header parser is being used to check if the data received so far has the length specified in the response headers
                var contentLength = HttpUtils.GetContentLength(state.responseContent.ToString());
                if (responseBody.Length < contentLength)
                {
                    // if the data received so far is less than the length specified in the response headers, get the next chunk of data
                    clientSocket.BeginReceive(state.receiveBuffer, 0, StateObject.BUFFER_SIZE, 0, OnReceive, state);
                }
                else
                {
                    // all the data has been received, print it
                    Console.WriteLine(state.responseContent);
                    
                    // close the connection
                    clientSocket.Shutdown(SocketShutdown.Both);
                    clientSocket.Close();
                }
            }
        }
        catch (Exception e)
        {
            Console.WriteLine(e.ToString());
        }
    }
}