package core.repository;

import core.domain.ArticleJournalistEntity;
import core.domain.ArticleJournalistPrimaryKey;
import core.domain.JournalistEntity;
import org.apache.commons.lang3.tuple.Pair;
import org.springframework.data.jpa.repository.Query;

import java.util.List;

public interface IArticleJournalistRepository extends IRepository<ArticleJournalistEntity, ArticleJournalistPrimaryKey> {
    @Query(value = "SELECT jrn.id AS id, jrn.last_name AS lastName, jrn.first_name AS firstName, jrn.email AS email, jrn.dob AS dob FROM journalist jrn WHERE jrn.id IN (SELECT aj.journalistid FROM article_journalist aj GROUP BY (aj.journalistid) ORDER BY COUNT(aj) DESC LIMIT 1)", nativeQuery = true)
    List<Object[]> getJournalistWithTheMostArticles();

}
