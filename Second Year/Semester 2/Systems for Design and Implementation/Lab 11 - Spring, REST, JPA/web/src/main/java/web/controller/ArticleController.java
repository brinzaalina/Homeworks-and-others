package web.controller;

import core.domain.ArticleEntity;
import core.service.IArticleService;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import web.converter.ArticleConverter;
import web.dto.ArticleDTO;
import web.dto.ArticlesDTO;

import java.util.List;

@RestController
public class ArticleController {
    public static final Logger logger = LoggerFactory.getLogger(ArticleController.class);

    @Autowired
    private IArticleService articleService;

    @Autowired
    private ArticleConverter articleConverter;

    @RequestMapping(value = "/articles")
    ArticlesDTO getArticlesFromRepository() {
        logger.trace("getAllArticles - method entered");
        List<ArticleEntity> articles = articleService.getAllArticles();
        ArticlesDTO articlesDTO = new ArticlesDTO(articleConverter.convertModelsToDTOs(articles));
        logger.trace("getAllArticles: " + articles);
        return articlesDTO;
    }

    @RequestMapping(value = "/articles", method = RequestMethod.POST)
    void addArticle(@RequestBody ArticleDTO articleDTO) {
        logger.trace("addArticle - method entered - articleDTO: " + articleDTO);
        var article = articleConverter.convertDtoToModel(articleDTO);
        articleService.addArticle(article.getTitle(), article.getText(), article.getCategoryId());
        logger.trace("addArticle - article added");
    }

    @RequestMapping(value = "/articles/{id}", method = RequestMethod.DELETE)
    ResponseEntity<?> deleteArticle(@PathVariable Long id) {
        articleService.deleteArticle(id);
        return new ResponseEntity<>(HttpStatus.OK);
    }

    @RequestMapping(value = "/articles/{id}", method = RequestMethod.PUT)
    void updateArticle(@PathVariable Long id, @RequestBody ArticleDTO articleDTO) {
        logger.trace("updateArticle - method entered - articleDTO: " + articleDTO);
        var article = articleConverter.convertDtoToModel(articleDTO);
        articleService.updateArticle(id, article.getTitle(), article.getText(), article.getCategoryId());
        logger.trace("updateArticle - article updated");
    }

    @RequestMapping(value = "/articles/filter/{categoryId}")
    ArticlesDTO filterArticlesByCategory(@PathVariable Long categoryId) {
        logger.trace("filterArticlesByCategory - method entered - categoryId = {}", categoryId);
        List<ArticleEntity> articles = articleService.filterArticlesByCategory(categoryId);
        ArticlesDTO articlesDTO = new ArticlesDTO(articleConverter.convertModelsToDTOs(articles));
        logger.trace("getAllArticles: " + articles);
        return articlesDTO;
    }
}

