package core.service;

import core.domain.ArticleEntity;

import java.util.List;

public interface IArticleService {
    List<ArticleEntity> getAllArticles();
    void addArticle(String title, String text, Long categoryId);
    void deleteArticle(Long id);
    void updateArticle(Long id, String title, String text, Long categoryId);
    List<ArticleEntity> filterArticlesByCategory(Long categoryId);
}
