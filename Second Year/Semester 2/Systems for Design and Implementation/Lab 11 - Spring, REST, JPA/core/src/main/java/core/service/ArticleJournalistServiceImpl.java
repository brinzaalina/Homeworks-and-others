package core.service;

import core.domain.ArticleJournalistEntity;
import core.domain.ArticleJournalistPrimaryKey;
import core.domain.JournalistEntity;
import core.domain.validators.ArticleJournalistValidator;
import core.exceptions.NewsException;
import core.repository.IArticleJournalistRepository;
import core.repository.IArticleRepository;
import core.repository.IJournalistRepository;
import org.apache.commons.lang3.tuple.Pair;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.math.BigInteger;
import java.util.Date;
import java.util.List;
import java.util.stream.Collectors;

@Service
public class ArticleJournalistServiceImpl implements  IArticleJournalistService{
    public static final Logger logger = LoggerFactory.getLogger(ArticleJournalistServiceImpl.class);

    @Autowired
    private ArticleJournalistValidator validator;

    @Autowired
    private IArticleJournalistRepository articleJournalistRepository;

    @Autowired
    private IArticleRepository articleRepository;

    @Autowired
    private IJournalistRepository journalistRepository;

    @Override
    public List<ArticleJournalistEntity> getAllArticleJournalists() {
        logger.trace("getAllArticleJournalists - method entered");
        List<ArticleJournalistEntity> articleJournalists = articleJournalistRepository.findAll();
        logger.trace("getAllArticleJournalists: " + articleJournalists);
        return articleJournalists;
    }

    @Override
    public void addArticleJournalist(Long articleId, Long journalistId) {
        logger.trace("addArticleJournalist - method entered - articleId: "+ articleId + ", journalistId: " + journalistId);
        articleRepository.findById(articleId)
                .ifPresentOrElse((article) -> {
                    journalistRepository.findById(journalistId)
                            .ifPresentOrElse(journalistEntity -> {
                                ArticleJournalistEntity articleJournalist = new ArticleJournalistEntity();
                                articleJournalist.setId(new ArticleJournalistPrimaryKey(articleId, journalistId));
                                validator.validate(articleJournalist);
                                articleJournalistRepository.save(articleJournalist);
                            }, () -> {
                                throw new NewsException("Journalist does not exist!");
                            });
                }, () -> {
                    throw new NewsException("Article does not exist!");
                });
        logger.trace("addArticleJournalist - method finished");
    }

    @Override
    public void deleteArticleJournalist(Long articleId, Long journalistId) {
        logger.trace("deleteArticleJournalist - method entered - articleId: " + articleId + ", journalistId: " + journalistId);
        articleJournalistRepository.findById(new ArticleJournalistPrimaryKey(articleId, journalistId))
                .ifPresentOrElse((articleJournalist) -> articleJournalistRepository.deleteById(new ArticleJournalistPrimaryKey(articleId, journalistId)),
                        () -> {
                            throw new NewsException("Article journalist does not exist!");
                        });
        logger.trace("deleteArticleJournalist - method finished");
    }

    @Override
    public JournalistEntity getJournalistWithTheMostArticles() {
        logger.trace("getJournalistWithTheMostArticles - method entered");
        var journalists = articleJournalistRepository.getJournalistWithTheMostArticles();
        List<Pair<JournalistEntity, Long>> toReturn = journalists.stream()
                        .map(obj -> Pair.of(new JournalistEntity((String)obj[1], (String) obj[2], (String) obj[3], (Date) obj[4]), ((BigInteger)obj[0]).longValue()))
                                .collect(Collectors.toList());
        var journalist = toReturn.get(0).getLeft();
        journalist.setId(toReturn.get(0).getRight());
        logger.trace("getJournalistWithTheMostArticles - method finished - result = {}", journalist);
        return journalist;
    }
}
