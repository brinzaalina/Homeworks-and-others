package ro.ubb.news.common;

import org.apache.commons.lang3.tuple.Pair;
import ro.ubb.news.common.domain.*;

import java.text.DateFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Arrays;
import java.util.Date;
import java.util.List;

public class Convertor {
    public static UserEntity extractUser(String dto) {
        List<String> tokens = Arrays.asList(dto.split(","));
        Long id = Long.parseLong(tokens.get(0));
        String lastName = tokens.get(1);
        String firstName = tokens.get(2);
        String email = tokens.get(3);
        long dobLong = Long.parseLong(tokens.get(4));
        Date dob = new Date();
        dob.setTime(dobLong);
        UserEntity newUser = new UserEntity(lastName, firstName, email);
        newUser.setId(id);
        newUser.setDob(dob);
        return newUser;
    }

    public static String convertUser(UserEntity user) {
        return user.getId() + "," +
                user.getLastName() + "," +
                user.getFirstName() + "," +
                user.getEmail() + "," +
                user.getDob().getTime();
    }

    public static JournalistEntity extractJournalist(String dto) {
        Long userId = Long.parseLong(dto);
        return new JournalistEntity(userId);
    }

    public static String convertJournalist(JournalistEntity journalist) {
        return journalist.getId().toString();
    }

    public static CategoryEntity extractCategory(String dto) {
        List<String> tokens = Arrays.asList(dto.split(","));
        Long id = Long.parseLong(tokens.get(0));
        String name = tokens.get(1);
        CategoryEntity newCategory = new CategoryEntity(name);
        newCategory.setId(id);
        return newCategory;
    }

    public static String convertCategory(CategoryEntity category) {
        return category.getId() + "," +
                category.getName();
    }

    public static ArticleEntity extractArticle(String dto) {
        List<String> tokens = Arrays.asList(dto.split(","));
        Long id = Long.parseLong(tokens.get(0));
        String title = tokens.get(1);
        String text = tokens.get(2);
        Long categoryId = Long.parseLong(tokens.get(3));
        ArticleEntity articleEntity = new ArticleEntity(title, text, categoryId);
        articleEntity.setId(id);
        return articleEntity;
    }

    public static String convertArticle(ArticleEntity article) {
        return article.getId() + "," +
                article.getTitle() + "," +
                article.getText() + "," +
                article.getCategoryId();
    }

    public static ArticleJournalistEntity extractArticleJournalist(String dto) {
        List<String> tokens = Arrays.asList(dto.split(","));
        Long articleId = Long.parseLong(tokens.get(0));
        Long journalistId = Long.parseLong(tokens.get(1));
        ArticleJournalistEntity newArticleJournalist = new ArticleJournalistEntity();
        newArticleJournalist.setId(Pair.of(articleId, journalistId));
        return newArticleJournalist;
    }

    public static String convertArticleJournalist(ArticleJournalistEntity articleJournalist) {
        return articleJournalist.getId().getLeft() + "," +
                articleJournalist.getId().getRight();
    }
}
