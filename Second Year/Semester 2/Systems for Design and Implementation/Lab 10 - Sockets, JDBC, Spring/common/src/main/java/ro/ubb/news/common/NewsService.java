package ro.ubb.news.common;

import ro.ubb.news.common.domain.*;

import java.util.Date;
import java.util.concurrent.CompletableFuture;

public interface NewsService {
    int PORT = 1234;
    String HOST = "localhost";

    String GET_USERS = "getAllUsers";
    String ADD_USER = "addUser";
    String DELETE_USER = "deleteUser";
    String UPDATE_USER = "updateUser";

    String GET_JOURNALISTS = "getAllJournalists";
    String ADD_JOURNALIST = "addJournalist";
    String DELETE_JOURNALIST = "deleteJournalist";

    String GET_CATEGORIES = "getAllCategories";
    String ADD_CATEGORY = "addCategory";
    String DELETE_CATEGORY = "deleteCategory";
    String UPDATE_CATEGORY = "updateCategory";

    String GET_ARTICLES = "getAllArticles";
    String ADD_ARTICLE = "addArticle";
    String DELETE_ARTICLE = "deleteArticle";
    String UPDATE_ARTICLE = "updateArticle";

    String GET_ARTICLE_JOURNALISTS = "getAllArticleJournalists";
    String ADD_ARTICLE_JOURNALIST = "addArticleJournalist";
    String DELETE_ARTICLE_JOURNALIST = "deleteArticleJournalist";
    String UPDATE_ARTICLE_JOURNALIST = "updateArticleJournalist";

    CompletableFuture<Iterable<UserEntity>> getAllUsers();
    CompletableFuture<String> addUser(String lastName, String firstName, String email, Date dob);
    CompletableFuture<String> deleteUser(Long id);
    CompletableFuture<String> updateUser(Long id, String lastName, String firstName, String email, Date dob);

    CompletableFuture<Iterable<JournalistEntity>> getAllJournalists();
    CompletableFuture<String> addJournalist(Long userId);
    CompletableFuture<String> deleteJournalist(Long userId);

    CompletableFuture<Iterable<CategoryEntity>> getAllCategories();
    CompletableFuture<String> addCategory(String name);
    CompletableFuture<String> deleteCategory(Long id);
    CompletableFuture<String> updateCategory(Long id, String name);

    CompletableFuture<Iterable<ArticleEntity>> getAllArticles();
    CompletableFuture<String> addArticle(String title, String text, Long categoryId);
    CompletableFuture<String> deleteArticle(Long id);
    CompletableFuture<String> updateArticle(Long id, String title, String text, Long categoryId);

    CompletableFuture<Iterable<ArticleJournalistEntity>> getAllArticleJournalists();
    CompletableFuture<String> addArticleJournalist(Long articleId, Long journalistId);
    CompletableFuture<String> deleteArticleJournalist(Long articleId, Long journalistId);
    CompletableFuture<String> updateArticleJournalist(Long articleId, Long journalistId);
}
