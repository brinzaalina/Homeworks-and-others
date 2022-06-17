package core.service;

import core.domain.ArticleEntity;
import core.domain.ArticleJournalistEntity;
import core.domain.ArticleJournalistPrimaryKey;
import core.domain.JournalistEntity;
import core.domain.validators.ArticleJournalistValidator;
import core.exceptions.NewsException;
//import core.repository.IArticleJournalistRepository;
import core.repository.IArticleRepository;
import core.repository.IJournalistRepository;
import org.apache.commons.lang3.tuple.Pair;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.math.BigInteger;
import java.util.*;
import java.util.concurrent.atomic.AtomicReference;
import java.util.stream.Collectors;

@Service
public class ArticleJournalistServiceImpl implements  IArticleJournalistService{
    public static final Logger logger = LoggerFactory.getLogger(ArticleJournalistServiceImpl.class);

    @Autowired
    private ArticleJournalistValidator validator;

    @Autowired
    private IArticleRepository articleRepository;

    @Autowired
    private IJournalistRepository journalistRepository;

    @Override
    public List<ArticleJournalistEntity> getAllArticleJournalists() {
        logger.trace("getAllArticleJournalists - method entered");
        List<ArticleEntity> articles = this.articleRepository.findAll();
        List<ArticleJournalistEntity> articleJournalists = articles.stream().flatMap(a -> a.getArticleJournalists().stream())
                        .collect(Collectors.toList());
        logger.trace("getAllArticleJournalists: " + articleJournalists);
        return articleJournalists;
    }

    @Override
    @Transactional
    public void addArticleJournalist(Long articleId, Long journalistId) {
        logger.trace("addArticleJournalist - method entered - articleId: "+ articleId + ", journalistId: " + journalistId);
        var article = articleRepository.findById(articleId);
        var journalist = journalistRepository.findById(journalistId);
        if (article.isPresent()) {
            if (journalist.isPresent()) {
                AtomicReference<Boolean> existsForArticle = new AtomicReference<>(false);
                AtomicReference<Boolean> existsForJournalist = new AtomicReference<>(false);
                Optional.of(article.get().getArticleJournalists()
                        .stream()
                        .anyMatch(aj -> aj.getArticle().getId().equals(articleId)))
                        .filter(bool -> bool.equals(true))
                        .ifPresent((trueVal) -> {
                            existsForArticle.set(true);
                        });
                Optional.of(journalist.get().getArticleJournalists()
                                .stream()
                                .anyMatch(aj -> aj.getJournalist().getId().equals(journalistId)))
                        .filter(bool -> bool.equals(true))
                        .ifPresent((trueVal) -> {
                            existsForJournalist.set(true);
                        });
                if (existsForArticle.get() && existsForJournalist.get()) {
                    throw new NewsException("Article-journalist already exists!");
                }
                var articleEntity = article.get();
                var journalistEntity = journalist.get();
                ArticleJournalistEntity articleJournalist = new ArticleJournalistEntity(journalistEntity, articleEntity);
                articleJournalist.setArticle(articleEntity);
                articleJournalist.setJournalist(journalistEntity);
                articleEntity.addJournalist(articleJournalist);
                journalistEntity.addArticle(articleJournalist);
            } else {
                throw new NewsException("Journalist does not exist!");
            }
        } else {
            throw new NewsException("Article does not exist!");
        }
        logger.trace("addArticleJournalist - method finished");
    }

    @Override
    @Transactional
    public void deleteArticleJournalist(Long articleId, Long journalistId) {
        logger.trace("deleteArticleJournalist - method entered - articleId: " + articleId + ", journalistId: " + journalistId);
        Optional<ArticleEntity> article = this.articleRepository.findById(articleId);
        Optional<JournalistEntity> journalist = this.journalistRepository.findById(journalistId);
        if (article.isPresent()) {
            if (journalist.isPresent()) {
                var articleEntity = article.get();
                var journalistEntity = journalist.get();
                articleEntity.removeArticleJournalist(journalistId);
                journalistEntity.removeArticleJournalist(articleId);
            } else {
                throw new NewsException("Journalist does not exist!");
            }
        } else {
            throw new NewsException("Article does not exist!");
        }
        logger.trace("deleteArticleJournalist - method finished");
    }

    @Override
    public JournalistEntity getJournalistWithTheMostArticles() {
        logger.trace("getJournalistWithTheMostArticles - method entered");
        var journalists = journalistRepository.findAll();
        List<Pair<JournalistEntity, Integer>> journalistsWithArticles = journalists.stream()
                .map(journalist -> Pair.of(journalist, journalist.getArticleJournalists().size()))
                .collect(Collectors.toList());
        Pair<JournalistEntity, Integer> journalist = journalistsWithArticles.stream()
                .max(Comparator.comparing(Pair::getRight))
                .orElseThrow(NoSuchElementException::new);
        logger.trace("getJournalistWithTheMostArticles - method finished - result = {}", journalist);
        return journalist.getLeft();
    }
}
