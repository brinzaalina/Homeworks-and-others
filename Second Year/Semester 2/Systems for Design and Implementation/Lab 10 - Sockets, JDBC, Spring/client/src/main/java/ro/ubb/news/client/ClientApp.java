package ro.ubb.news.client;

import ro.ubb.news.client.service.ClientNewsService;
import ro.ubb.news.client.tcp.TcpClient;
import ro.ubb.news.client.ui.UI;
import ro.ubb.news.common.NewsService;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class ClientApp {
    public static void main(String[] args) {
        ExecutorService executorService = Executors.newFixedThreadPool(
                Runtime.getRuntime().availableProcessors()
        );

        TcpClient tcpClient = new TcpClient();
        NewsService newsService = new ClientNewsService(executorService, tcpClient);
        UI clientConsole = new UI(newsService);
        clientConsole.run();
        executorService.shutdown();
    }
}
