package ro.ubb.news.client.tcp;

import ro.ubb.news.common.Message;
import ro.ubb.news.common.NewsService;
import ro.ubb.news.common.exceptions.NewsServiceException;

import java.io.IOException;
import java.net.ConnectException;
import java.net.Socket;

public class TcpClient {
    public Message sendAndReceive(Message request) {
        try (var socket = new Socket(NewsService.HOST, NewsService.PORT);
        var is = socket.getInputStream();
        var os = socket.getOutputStream()) {
            System.out.println("Sending request: " + request);
            request.writeTo(os);
            System.out.println("Request sent");

            Message response = new Message();
            response.readFrom(is);
            System.out.println("Received response: " + response);
            return response;
        } catch (ConnectException ce) {
            throw new NewsServiceException("Could not establish connection with the server");
        } catch (IOException e) {
            throw new NewsServiceException("Exception in send and receive", e);
        }
    }
}
