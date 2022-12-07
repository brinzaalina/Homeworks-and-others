using A4.Model;

namespace A4.Utils;

public class HttpUtils
{
    public static readonly int HTTP_PORT = 80;

    public static string GetResponseBody(string responseContent)
    {
        var responseParts = responseContent.Split(new[] { "\r\n\r\n" }, StringSplitOptions.RemoveEmptyEntries);
        return responseParts.Length > 1 ? responseParts[1] : "";
    }

    public static bool ResponseHeaderFullyObtained(string responseContent)
    {
        return responseContent.Contains("\r\n\r\n");
    }

    public static int GetContentLength(string responseContent)
    {
        var responseLines = responseContent.Split('\r', '\n');
        foreach (var responseLine in responseLines)
        {
            var headerDetails = responseLine.Split(':');
            if (headerDetails[0].CompareTo("Content-Length") == 0)
            {
                return int.Parse(headerDetails[1]);
            }
        }

        return 0;
    }

    public static string GetRequestString(string hostname, string endpoint)
    {
        return "GET " + endpoint + " HTTP/1.1\r\n" +
               "Host: " + hostname + "\r\n" +
               "Content-Length: 0\r\n\r\n" +
               "Content-Type: text/html";
    }
    
    public static void PrintResponse(StateObject state)
    {
        foreach (var i in state.responseContent.ToString().Split('\r', '\n'))
        {
            Console.WriteLine(i);
        }
    }
}