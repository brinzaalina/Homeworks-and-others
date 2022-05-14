package web.controller;

import core.domain.ArticleJournalistEntity;
import core.service.IArticleJournalistService;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import web.converter.ArticleJournalistConverter;
import web.converter.JournalistConverter;
import web.dto.ArticleJournalistDTO;
import web.dto.ArticleJournalistPrimaryKeyDTO;
import web.dto.ArticleJournalistsDTO;
import web.dto.JournalistDTO;

import java.util.List;

@RestController
public class ArticleJournalistController {
    public static final Logger logger = LoggerFactory.getLogger(ArticleJournalistController.class);

    @Autowired
    private IArticleJournalistService articleJournalistService;

    @Autowired
    private ArticleJournalistConverter articleJournalistConverter;

    @Autowired
    private JournalistConverter journalistConverter;

    @RequestMapping(value = "/articles-journalists")
    ArticleJournalistsDTO getArticleJournalistsFromRepository() {
        logger.trace("getAllArticleJournalists - method entered");
        List<ArticleJournalistEntity> articleJournalists = articleJournalistService.getAllArticleJournalists();
        ArticleJournalistsDTO articleJournalistsDTO = new ArticleJournalistsDTO(articleJournalistConverter.convertModelsToDTOs(articleJournalists));
        logger.trace("getAllArticleJournalists: " + articleJournalists);
        return articleJournalistsDTO;
    }

    @RequestMapping(value = "/articles-journalists", method = RequestMethod.POST)
    void addArticleJournalist(@RequestBody ArticleJournalistPrimaryKeyDTO articleJournalistPrimaryKeyDTO) {
        logger.trace("addArticleJournalist - method entered - articleJournalistPrimaryKeyDTO: " + articleJournalistPrimaryKeyDTO);
        articleJournalistService.addArticleJournalist(articleJournalistPrimaryKeyDTO.getArticleId(), articleJournalistPrimaryKeyDTO.getJournalistId());
        logger.trace("addArticleJournalist - article journalist added");
    }

    @RequestMapping(value = "/articles-journalists/{articleId}&{journalistId}", method = RequestMethod.DELETE)
    ResponseEntity<?> deleteArticleJournalist(@PathVariable Long articleId, @PathVariable Long journalistId) {
        articleJournalistService.deleteArticleJournalist(articleId, journalistId);
        return new ResponseEntity<>(HttpStatus.OK);
    }

    @RequestMapping(value = "/articles-journalists/most")
    JournalistDTO getJournalistWithTheMostArticles() {
        logger.trace("getJournalistWithTheMostArticles - method entered");
        var journalist = journalistConverter.convertModelToDto(articleJournalistService.getJournalistWithTheMostArticles());
        logger.trace("getJournalistWithTheMostArticles: " + journalist);
        return journalist;
    }
}
