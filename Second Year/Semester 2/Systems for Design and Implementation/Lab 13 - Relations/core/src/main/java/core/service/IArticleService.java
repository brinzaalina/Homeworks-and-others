package core.service;

import core.domain.ArticleEntity;
import core.domain.CategoryEntity;

import java.util.List;

public interface IArticleService {
    List<ArticleEntity> getAllArticles();
    void addArticle(String title, String text, CategoryEntity category);
    void deleteArticle(Long id);
    void updateArticle(Long id, String title, String text, CategoryEntity category);
    List<ArticleEntity> filterArticlesByCategory(Long category);
}
