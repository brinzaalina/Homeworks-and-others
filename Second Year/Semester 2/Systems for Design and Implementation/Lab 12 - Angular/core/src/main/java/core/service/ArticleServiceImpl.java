package core.service;

import core.domain.ArticleEntity;
import core.domain.validators.ArticleValidator;
import core.exceptions.NewsException;
import core.repository.IArticleJournalistRepository;
import core.repository.IArticleRepository;
import core.repository.ICategoryRepository;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.util.List;

@Service
public class ArticleServiceImpl implements IArticleService {
    public static final Logger logger = LoggerFactory.getLogger(ArticleServiceImpl.class);

    @Autowired
    private ArticleValidator validator;

    @Autowired
    private ICategoryRepository categoryRepository;

    @Autowired
    private IArticleRepository articleRepository;

    @Autowired
    private IArticleJournalistRepository articleJournalistRepository;

    @Override
    public List<ArticleEntity> getAllArticles() {
        logger.trace("getAllArticles - method entered");
        List<ArticleEntity> articles = articleRepository.findAll();
        logger.trace("getAllArticles: " + articles);
        return articles;
    }

    @Override
    public void addArticle(String title, String text, Long categoryId) {
        logger.trace("addArticle - method entered - title: " + title + ", text: " + text + ", categoryId: " + categoryId);
        categoryRepository.findById(categoryId)
                .ifPresentOrElse((category) -> {
                    ArticleEntity article = new ArticleEntity(title, text, categoryId);
                    validator.validate(article);
                    articleRepository.save(article);
                }, () -> {
                    throw new NewsException("Category does not exist!");
                });
        logger.trace("addArticle - method finished");
    }

    @Override
    public void deleteArticle(Long id) {
        logger.trace("deleteArticle - method entered - id: " + id);
        articleJournalistRepository.findAll().stream()
                .filter(articleJournalist -> articleJournalist.getId().getArticleid().equals(id))
                .findAny()
                .ifPresent((articleJournalist -> {
                    throw new NewsException("Article is assigned to a journalist!");
                }));
        articleRepository.findById(id)
                .ifPresentOrElse((article) -> articleRepository.deleteById(article.getId()), () -> {
                    throw new NewsException("Article does not exist!");
                });
        logger.trace("deleteArticle - method finished");
    }

    @Override
    @Transactional
    public void updateArticle(Long id, String title, String text, Long categoryId) {
        logger.trace("updateArticle - method entered - id: " + id + ", title: " + title + ", text: " + text + ", categoryId: " + categoryId);
        ArticleEntity articleEntity = new ArticleEntity(title, text, categoryId);
        articleEntity.setId(id);
        validator.validate(articleEntity);
        categoryRepository.findById(categoryId)
                .ifPresentOrElse((category) -> {
                    articleRepository.findById(id)
                            .ifPresentOrElse((article) -> {
                                article.setTitle(title);
                                article.setText(text);
                                article.setCategoryId(category.getId());
                            }, () -> {
                                throw new NewsException("Article does not exist!");
                            });
                }, () -> {
                    throw new NewsException("Category does not exist!");
                });
        logger.trace("updateArticle - method finished");
    }

    @Override
    public List<ArticleEntity> filterArticlesByCategory(Long categoryId) {
        logger.trace("filterArticlesByCategory - method entered - categoryId = {}", categoryId);
        var result = articleRepository.findAllByCategoryId(categoryId);
        logger.trace("filterArticlesByCategory - method finished - result = {}", result);
        return result;
    }
}
