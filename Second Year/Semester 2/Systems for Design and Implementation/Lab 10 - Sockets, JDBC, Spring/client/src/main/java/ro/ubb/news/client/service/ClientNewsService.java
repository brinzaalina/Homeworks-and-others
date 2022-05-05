package ro.ubb.news.client.service;

import org.apache.commons.lang3.StringUtils;
import org.apache.commons.lang3.tuple.Pair;
import ro.ubb.news.client.tcp.TcpClient;
import ro.ubb.news.common.Convertor;
import ro.ubb.news.common.Message;
import ro.ubb.news.common.NewsService;
import ro.ubb.news.common.domain.*;

import java.util.Arrays;
import java.util.Date;
import java.util.LinkedList;
import java.util.List;
import java.util.concurrent.CompletableFuture;
import java.util.concurrent.ExecutorService;

import static ro.ubb.news.common.Convertor.*;

public class ClientNewsService implements NewsService {
    private final ExecutorService executorService;
    private final TcpClient tcpClient;

    public ClientNewsService(ExecutorService executorService, TcpClient tcpClient) {
        this.executorService = executorService;
        this.tcpClient = tcpClient;
    }

    @Override
    public CompletableFuture<Iterable<UserEntity>> getAllUsers() {
        return CompletableFuture.supplyAsync(() -> {
            Message request = new Message(NewsService.GET_USERS, "");
            Message response = tcpClient.sendAndReceive(request);
            String result = response.getBody();
            List<UserEntity> users = new LinkedList<>();
            if (StringUtils.isNotEmpty(result))
                Arrays.stream(result.split(";"))
                        .map(Convertor::extractUser)
                        .forEach(users::add);
            return users;
        }, executorService);
    }

    @Override
    public CompletableFuture<String> addUser(String lastName, String firstName, String email, Date dob) {
        return CompletableFuture.supplyAsync(() -> {
            Message request = new Message(NewsService.ADD_USER, lastName + "," + firstName + "," + email + "," + dob.getTime());
            return tcpClient.sendAndReceive(request).getBody();
        }, executorService);
    }

    @Override
    public CompletableFuture<String> deleteUser(Long id) {
        return CompletableFuture.supplyAsync(() -> {
            Message request = new Message(NewsService.DELETE_USER, id.toString());
            return tcpClient.sendAndReceive(request).getBody();
        }, executorService);
    }

    @Override
    public CompletableFuture<String> updateUser(Long id, String lastName, String firstName, String email, Date dob) {
        return CompletableFuture.supplyAsync(() -> {
            UserEntity user = new UserEntity(lastName, firstName, email);
            user.setId(id);
            user.setDob(dob);
            Message request = new Message(NewsService.UPDATE_USER, convertUser(user));
            return tcpClient.sendAndReceive(request).getBody();
        }, executorService);
    }

    @Override
    public CompletableFuture<Iterable<JournalistEntity>> getAllJournalists() {
        return CompletableFuture.supplyAsync(() -> {
            Message request = new Message(NewsService.GET_JOURNALISTS, "");
            Message response = tcpClient.sendAndReceive(request);
            String result = response.getBody();
            List<JournalistEntity> journalists = new LinkedList<>();
            if (StringUtils.isNotEmpty(result))
                Arrays.stream(result.split(";"))
                        .map(Convertor::extractJournalist)
                        .forEach(journalists::add);
            return journalists;
        }, executorService);
    }

    @Override
    public CompletableFuture<String> addJournalist(Long userId) {
        return CompletableFuture.supplyAsync(() -> {
            Message request = new Message(NewsService.ADD_JOURNALIST, userId.toString());
            return tcpClient.sendAndReceive(request).getBody();
        }, executorService);
    }

    @Override
    public CompletableFuture<String> deleteJournalist(Long userId) {
        return CompletableFuture.supplyAsync(() -> {
            Message request = new Message(NewsService.DELETE_JOURNALIST, userId.toString());
            return tcpClient.sendAndReceive(request).getBody();
        }, executorService);
    }


    @Override
    public CompletableFuture<Iterable<CategoryEntity>> getAllCategories() {
        return CompletableFuture.supplyAsync(() -> {
            Message request = new Message(NewsService.GET_CATEGORIES, "");
            Message response = tcpClient.sendAndReceive(request);
            String result = response.getBody();
            List<CategoryEntity> categories = new LinkedList<>();
            if (StringUtils.isNotEmpty(result))
                Arrays.stream(result.split(";"))
                        .map(Convertor::extractCategory)
                        .forEach(categories::add);
            return categories;
        }, executorService);
    }

    @Override
    public CompletableFuture<String> addCategory(String name) {
        return CompletableFuture.supplyAsync(() -> {
            Message request = new Message(NewsService.ADD_CATEGORY, name);
            return tcpClient.sendAndReceive(request).getBody();
        }, executorService);
    }

    @Override
    public CompletableFuture<String> deleteCategory(Long id) {
        return CompletableFuture.supplyAsync(() -> {
            Message request = new Message(NewsService.DELETE_CATEGORY, id.toString());
            return tcpClient.sendAndReceive(request).getBody();
        }, executorService);
    }

    @Override
    public CompletableFuture<String> updateCategory(Long id, String name) {
        return CompletableFuture.supplyAsync(() -> {
            CategoryEntity category = new CategoryEntity(name);
            category.setId(id);
            Message request = new Message(NewsService.UPDATE_CATEGORY, convertCategory(category));
            return tcpClient.sendAndReceive(request).getBody();
        }, executorService);
    }

    @Override
    public CompletableFuture<Iterable<ArticleEntity>> getAllArticles() {
        return CompletableFuture.supplyAsync(() -> {
            Message request = new Message(NewsService.GET_ARTICLES, "");
            Message response = tcpClient.sendAndReceive(request);
            String result = response.getBody();
            List<ArticleEntity> articles = new LinkedList<>();
            if (StringUtils.isNotEmpty(result))
                Arrays.stream(result.split(";"))
                        .map(Convertor::extractArticle)
                        .forEach(articles::add);
            return articles;
        }, executorService);
    }

    @Override
    public CompletableFuture<String> addArticle(String title, String text, Long categoryId) {
        return CompletableFuture.supplyAsync(() -> {
            Message request = new Message(NewsService.ADD_ARTICLE, title + "," + text + "," + categoryId);
            return tcpClient.sendAndReceive(request).getBody();
        }, executorService);
    }

    @Override
    public CompletableFuture<String> deleteArticle(Long id) {
        return CompletableFuture.supplyAsync(() -> {
            Message request = new Message(NewsService.DELETE_ARTICLE, id.toString());
            return tcpClient.sendAndReceive(request).getBody();
        }, executorService);
    }

    @Override
    public CompletableFuture<String> updateArticle(Long id, String title, String text, Long categoryId) {
        return CompletableFuture.supplyAsync(() -> {
            ArticleEntity article = new ArticleEntity(title, text, categoryId);
            article.setId(id);
            Message request = new Message(NewsService.UPDATE_ARTICLE, convertArticle(article));
            return tcpClient.sendAndReceive(request).getBody();
        }, executorService);
    }


    @Override
    public CompletableFuture<Iterable<ArticleJournalistEntity>> getAllArticleJournalists() {
        return CompletableFuture.supplyAsync(() -> {
            Message request = new Message(NewsService.GET_ARTICLE_JOURNALISTS, "");
            Message response = tcpClient.sendAndReceive(request);
            String result = response.getBody();
            List<ArticleJournalistEntity> articleJournalists = new LinkedList<>();
            if (StringUtils.isNotEmpty(result))
                Arrays.stream(result.split(";"))
                        .map(Convertor::extractArticleJournalist)
                        .forEach(articleJournalists::add);
            return articleJournalists;
        }, executorService);
    }

    @Override
    public CompletableFuture<String> addArticleJournalist(Long articleId, Long journalistId) {
        return CompletableFuture.supplyAsync(() -> {
            Message request = new Message(NewsService.ADD_ARTICLE_JOURNALIST, articleId + "," + journalistId);
            return tcpClient.sendAndReceive(request).getBody();
        }, executorService);
    }

    @Override
    public CompletableFuture<String> deleteArticleJournalist(Long articleId, Long journalistId) {
        return CompletableFuture.supplyAsync(() -> {
            Message request = new Message(NewsService.DELETE_ARTICLE_JOURNALIST, articleId.toString() + "," + journalistId.toString());
            return tcpClient.sendAndReceive(request).getBody();
        }, executorService);
    }

    @Override
    public CompletableFuture<String> updateArticleJournalist(Long articleId, Long journalistId) {
        return CompletableFuture.supplyAsync(() -> {
            ArticleJournalistEntity articleJournalist = new ArticleJournalistEntity();
            articleJournalist.setId(Pair.of(articleId, journalistId));
            Message request = new Message(NewsService.UPDATE_ARTICLE_JOURNALIST, convertArticleJournalist(articleJournalist));
            return tcpClient.sendAndReceive(request).getBody();
        }, executorService);
    }
}
