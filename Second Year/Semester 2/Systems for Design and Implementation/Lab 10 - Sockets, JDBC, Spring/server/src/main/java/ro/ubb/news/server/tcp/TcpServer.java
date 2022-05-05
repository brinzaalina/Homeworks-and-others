package ro.ubb.news.server.tcp;

import org.springframework.beans.factory.annotation.Autowired;
import ro.ubb.news.common.Message;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.ExecutorService;
import java.util.function.UnaryOperator;

public class TcpServer {
    @Autowired
    private ExecutorService executorService;
    private final int port;
    private final Map<String, UnaryOperator<Message>> methodHandlers;

    public TcpServer(int port) {
        this.port = port;
        this.methodHandlers = new HashMap<>();
    }

    public void addHandler(String methodName, UnaryOperator<Message> handler) {
        methodHandlers.put(methodName, handler);
    }

    public void startServer() {
        try (var serverSocket = new ServerSocket(this.port)) {
            System.out.println("Server started; waiting for clients...");
            while (true) {
                Socket clientSocket = serverSocket.accept();
                System.out.println("Client connected");
                executorService.submit(new ClientHandler(clientSocket));
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private class ClientHandler implements Runnable {
        private final Socket socket;

        private ClientHandler(Socket socket) {
            this.socket = socket;
        }

        @Override
        public void run() {
            try (var is = socket.getInputStream();
            var os = socket.getOutputStream()) {
                Message request = new Message();
                request.readFrom(is);
                System.out.println("Received request: " + request);

                Message response = methodHandlers.get(request.getHeader()).apply(request);
                System.out.println("Computed response: " + response);

                response.writeTo(os);
                System.out.println("Response sent to client");
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
}
