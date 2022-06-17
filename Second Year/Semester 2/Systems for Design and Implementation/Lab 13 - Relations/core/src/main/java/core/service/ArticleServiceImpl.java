package core.service;

import core.domain.ArticleEntity;
import core.domain.CategoryEntity;
import core.domain.validators.ArticleValidator;
import core.exceptions.NewsException;
//import core.repository.IArticleJournalistRepository;
import core.repository.IArticleRepository;
import core.repository.ICategoryRepository;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.atomic.AtomicReference;

@Service
public class ArticleServiceImpl implements IArticleService {
    public static final Logger logger = LoggerFactory.getLogger(ArticleServiceImpl.class);

    @Autowired
    private ArticleValidator validator;

    @Autowired
    private ICategoryRepository categoryRepository;

    @Autowired
    private IArticleRepository articleRepository;

    @Override
    public List<ArticleEntity> getAllArticles() {
        logger.trace("getAllArticles - method entered");
        List<ArticleEntity> articles = articleRepository.findAll();
        logger.trace("getAllArticles: " + articles);
        return articles;
    }

    @Override
    @Transactional
    public void addArticle(String title, String text, CategoryEntity category) {
        logger.trace("addArticle - method entered - title: " + title + ", text: " + text + ", categoryId: " + category.getId());
        categoryRepository.findById(category.getId())
                .ifPresentOrElse((cat) -> {
                    ArticleEntity article = ArticleEntity.builder().title(title).text(text).category(category).build();
                    validator.validate(article);
                    articleRepository.save(article);
                    cat.addArticle(article);
                }, () -> {
                    throw new NewsException("Category does not exist!");
                });
        logger.trace("addArticle - method finished");
    }

    @Override
    public void deleteArticle(Long id) {
        logger.trace("deleteArticle - method entered - id: " + id);
        articleRepository.findById(id)
                .ifPresentOrElse((article) -> articleRepository.deleteById(article.getId()), () -> {
                    throw new NewsException("Article does not exist!");
                });
        logger.trace("deleteArticle - method finished");
    }

    @Override
    @Transactional
    public void updateArticle(Long id, String title, String text, CategoryEntity category) {
        logger.trace("updateArticle - method entered - id: " + id + ", title: " + title + ", text: " + text + ", categoryId: " + category.getId());
        ArticleEntity articleEntity = ArticleEntity.builder().title(title).text(text).category(category).build();
        articleEntity.setId(id);
        validator.validate(articleEntity);
        categoryRepository.findById(category.getId())
                .ifPresentOrElse((cat) -> articleRepository.findById(id)
                        .ifPresentOrElse((article) -> {
                            article.setTitle(title);
                            article.setText(text);
                            article.setCategory(category);
                            category.addArticle(article);
                        }, () -> {
                            throw new NewsException("Article does not exist!");
                        }), () -> {
                    throw new NewsException("Category does not exist!");
                });
        logger.trace("updateArticle - method finished");
    }

    @Override
    public List<ArticleEntity> filterArticlesByCategory(Long categoryId) {
        logger.trace("filterArticlesByCategory - method entered - categoryId = {}", categoryId);
        List<ArticleEntity> result;
        var category = categoryRepository.findById(categoryId);
        if (category.isPresent())
            result = articleRepository.findAllByCategory(category.get());
        else
            throw new NewsException("Category does not exist");
        logger.trace("filterArticlesByCategory - method finished - result = {}", result);
        return result;
    }
}
