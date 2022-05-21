package core.service;

import core.domain.ArticleJournalistEntity;
import core.domain.JournalistEntity;

import java.util.List;

public interface IArticleJournalistService {
    List<ArticleJournalistEntity> getAllArticleJournalists();
    void addArticleJournalist(Long articleId, Long journalistId);
    void deleteArticleJournalist(Long articleId, Long journalistId);
    JournalistEntity getJournalistWithTheMostArticles();
}
