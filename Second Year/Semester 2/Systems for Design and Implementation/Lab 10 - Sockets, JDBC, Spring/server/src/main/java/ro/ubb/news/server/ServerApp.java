package ro.ubb.news.server;

import org.springframework.context.annotation.AnnotationConfigApplicationContext;
import ro.ubb.news.common.Convertor;
import ro.ubb.news.common.Message;
import ro.ubb.news.common.NewsService;
import ro.ubb.news.common.domain.ArticleEntity;
import ro.ubb.news.common.domain.ArticleJournalistEntity;
import ro.ubb.news.common.domain.CategoryEntity;
import ro.ubb.news.common.domain.UserEntity;
import ro.ubb.news.server.service.ServerNewsService;
import ro.ubb.news.server.tcp.TcpServer;

import java.util.Date;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

public class ServerApp {
    public static void main(String[] args) {
        AnnotationConfigApplicationContext context = new AnnotationConfigApplicationContext("ro.ubb.news.server.config");
        ServerNewsService service = context.getBean(ServerNewsService.class);
        TcpServer tcpServer = context.getBean(TcpServer.class);

        //user
        tcpServer.addHandler(NewsService.GET_USERS, request -> {
            try {
                return new Message(Message.OK,
                        StreamSupport.stream(service.getAllUsers().get().spliterator(), false)
                                .map(Convertor::convertUser)
                                .collect(Collectors.joining(";")));
            } catch (ExecutionException | InterruptedException e) {
                e.printStackTrace();
                return new Message(Message.ERROR, e.getMessage());
            }
        });

        tcpServer.addHandler(NewsService.ADD_USER, request -> {
            try {
                String[] splitUser = request.getBody().split(",");
                Date dob = new Date(Long.parseLong(splitUser[3]));
                String status = service.addUser(splitUser[0], splitUser[1], splitUser[2], dob).get();
                return new Message(Message.OK, status);
            } catch (ExecutionException | InterruptedException e) {
                e.printStackTrace();
                return new Message(Message.ERROR, e.getMessage());
            }
        });

        tcpServer.addHandler(NewsService.DELETE_USER, request -> {
            try {
                String status = service.deleteUser(Long.parseLong(request.getBody())).get();
                return new Message(Message.OK, status);
            } catch (ExecutionException | InterruptedException e) {
                e.printStackTrace();
                return new Message(Message.ERROR, e.getMessage());
            }
        });

        tcpServer.addHandler(NewsService.UPDATE_USER, request -> {
            try {
                UserEntity user = Convertor.extractUser(request.getBody());
                String status = service.updateUser(user.getId(), user.getLastName(), user.getFirstName(), user.getEmail(), user.getDob()).get();
                return new Message(Message.OK, status);
            } catch (ExecutionException | InterruptedException e) {
                e.printStackTrace();
                return new Message(Message.ERROR, e.getMessage());
            }
        });

        //journalist
        tcpServer.addHandler(NewsService.GET_JOURNALISTS, request -> {
            try {
                return new Message(Message.OK,
                        StreamSupport.stream(service.getAllJournalists().get().spliterator(), false)
                                .map(Convertor::convertJournalist)
                                .collect(Collectors.joining(";")));
            } catch (ExecutionException | InterruptedException e) {
                e.printStackTrace();
                return new Message(Message.ERROR, e.getMessage());
            }
        });

        tcpServer.addHandler(NewsService.ADD_JOURNALIST, request -> {
            try {
                Long journalist = Long.parseLong(request.getBody());
                String status = service.addJournalist(journalist).get();
                return new Message(Message.OK, status);
            } catch (ExecutionException | InterruptedException e) {
                e.printStackTrace();
                return new Message(Message.ERROR, e.getMessage());
            }
        });

        tcpServer.addHandler(NewsService.DELETE_JOURNALIST, request -> {
            try {
                String status = service.deleteJournalist(Long.parseLong(request.getBody())).get();
                return new Message(Message.OK, status);
            } catch (ExecutionException | InterruptedException e) {
                e.printStackTrace();
                return new Message(Message.ERROR, e.getMessage());
            }
        });

        //category
        tcpServer.addHandler(NewsService.GET_CATEGORIES, request -> {
            try {
                return new Message(Message.OK,
                        StreamSupport.stream(service.getAllCategories().get().spliterator(), false)
                                .map(Convertor::convertCategory)
                                .collect(Collectors.joining(";")));
            } catch (ExecutionException | InterruptedException e) {
                e.printStackTrace();
                return new Message(Message.ERROR, e.getMessage());
            }
        });

        tcpServer.addHandler(NewsService.ADD_CATEGORY, request -> {
            try {
                String category = request.getBody();
                String status = service.addCategory(category).get();
                return new Message(Message.OK, status);
            } catch (ExecutionException | InterruptedException e) {
                e.printStackTrace();
                return new Message(Message.ERROR, e.getMessage());
            }
        });

        tcpServer.addHandler(NewsService.DELETE_CATEGORY, request -> {
            try {
                String status = service.deleteCategory(Long.parseLong(request.getBody())).get();
                return new Message(Message.OK, status);
            } catch (ExecutionException | InterruptedException e) {
                e.printStackTrace();
                return new Message(Message.ERROR, e.getMessage());
            }
        });

        tcpServer.addHandler(NewsService.UPDATE_CATEGORY, request -> {
            try {
                CategoryEntity category = Convertor.extractCategory(request.getBody());
                String status = service.updateCategory(category.getId(), category.getName()).get();
                return new Message(Message.OK, status);
            } catch (ExecutionException | InterruptedException e) {
                e.printStackTrace();
                return new Message(Message.ERROR, e.getMessage());
            }
        });

        //article
        tcpServer.addHandler(NewsService.GET_ARTICLES, request -> {
            try {
                return new Message(Message.OK,
                        StreamSupport.stream(service.getAllArticles().get().spliterator(), false)
                                .map(Convertor::convertArticle)
                                .collect(Collectors.joining(";")));
            } catch (ExecutionException | InterruptedException e) {
                e.printStackTrace();
                return new Message(Message.ERROR, e.getMessage());
            }
        });

        tcpServer.addHandler(NewsService.ADD_ARTICLE, request -> {
            try {
                String[] splitArticle = request.getBody().split(",");
                String status = service.addArticle(splitArticle[0], splitArticle[1], Long.parseLong(splitArticle[2])).get();
                return new Message(Message.OK, status);
            } catch (ExecutionException | InterruptedException e) {
                e.printStackTrace();
                return new Message(Message.ERROR, e.getMessage());
            }
        });

        tcpServer.addHandler(NewsService.DELETE_ARTICLE, request -> {
            try {
                String status = service.deleteArticle(Long.parseLong(request.getBody())).get();
                return new Message(Message.OK, status);
            } catch (ExecutionException | InterruptedException e) {
                e.printStackTrace();
                return new Message(Message.ERROR, e.getMessage());
            }
        });

        tcpServer.addHandler(NewsService.UPDATE_ARTICLE, request -> {
            try {
                ArticleEntity article = Convertor.extractArticle(request.getBody());
                String status = service.updateArticle(article.getId(), article.getTitle(), article.getText(), article.getCategoryId()).get();
                return new Message(Message.OK, status);
            } catch (ExecutionException | InterruptedException e) {
                e.printStackTrace();
                return new Message(Message.ERROR, e.getMessage());
            }
        });

        //article-journalist
        tcpServer.addHandler(NewsService.GET_ARTICLE_JOURNALISTS, request -> {
            try {
                return new Message(Message.OK,
                        StreamSupport.stream(service.getAllArticleJournalists().get().spliterator(), false)
                                .map(Convertor::convertArticleJournalist)
                                .collect(Collectors.joining(";")));
            } catch (ExecutionException | InterruptedException e) {
                e.printStackTrace();
                return new Message(Message.ERROR, e.getMessage());
            }
        });

        tcpServer.addHandler(NewsService.ADD_ARTICLE_JOURNALIST, request -> {
            try {
                String[] articleJournalist = request.getBody().split(",");
                String status = service.addArticleJournalist(Long.parseLong(articleJournalist[0]), Long.parseLong(articleJournalist[1])).get();
                return new Message(Message.OK, status);
            } catch (ExecutionException | InterruptedException e) {
                e.printStackTrace();
                return new Message(Message.ERROR, e.getMessage());
            }
        });

        tcpServer.addHandler(NewsService.DELETE_ARTICLE_JOURNALIST, request -> {
            try {
                String[] articleJournalist = request.getBody().split(",");
                String status = service.deleteArticleJournalist(Long.parseLong(articleJournalist[0]), Long.parseLong(articleJournalist[1])).get();
                return new Message(Message.OK, status);
            } catch (ExecutionException | InterruptedException e) {
                e.printStackTrace();
                return new Message(Message.ERROR, e.getMessage());
            }
        });

        tcpServer.addHandler(NewsService.UPDATE_ARTICLE_JOURNALIST, request -> {
            try {
                ArticleJournalistEntity articleJournalist = Convertor.extractArticleJournalist(request.getBody());
                String status = service.updateArticleJournalist(articleJournalist.getId().getLeft(), articleJournalist.getId().getRight()).get();
                return new Message(Message.OK, status);
            } catch (ExecutionException | InterruptedException e) {
                e.printStackTrace();
                return new Message(Message.ERROR, e.getMessage());
            }
        });

        tcpServer.startServer();
    }
}
