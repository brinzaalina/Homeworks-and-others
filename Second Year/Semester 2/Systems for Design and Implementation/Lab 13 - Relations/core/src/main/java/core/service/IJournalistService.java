package core.service;

import core.domain.ArticleEntity;
import core.domain.JournalistEntity;

import java.util.Date;
import java.util.List;
import java.util.Set;

public interface IJournalistService {
    List<JournalistEntity> getAllJournalists();
    void addJournalist(String lastName, String firstName, String email, Date dob);
    void deleteJournalist(Long id);
    void updateJournalist(Long id, String lastName, String firstName, String email, Date dob);
    List<JournalistEntity> getAllJournalistsBornBefore(Date date);
    Set<ArticleEntity> getArticlesOfJournalist(Long id);
    void assignToArticle(Long journalistId, String articleTitle);
}

