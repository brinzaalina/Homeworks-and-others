package ro.ubb.news.server.repository;

import org.apache.commons.lang3.tuple.Pair;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.jdbc.core.JdbcOperations;
import ro.ubb.news.common.domain.ArticleJournalistEntity;
import ro.ubb.news.common.domain.CategoryEntity;
import ro.ubb.news.common.domain.validators.Validator;
import ro.ubb.news.common.exceptions.ValidatorException;

import java.util.HashSet;
import java.util.Optional;

public class ArticleJournalistDatabaseRepository implements IRepository<Pair<Long, Long>, ArticleJournalistEntity> {
    @Autowired
    private JdbcOperations jdbcOperations;

    @Autowired
    private Validator<ArticleJournalistEntity> validator;

//    public ArticleJournalistDatabaseRepository(Validator<ArticleJournalistEntity> validator) {
//        this.validator = validator;
//    }

    @Override
    public Optional<ArticleJournalistEntity> findOne(Pair<Long, Long> longLongPair) {
        String sql = String.format("SELECT * FROM article_journalist WHERE articleid = %d AND journalistid = %d", longLongPair.getLeft(), longLongPair.getRight());
        return jdbcOperations.query(sql, (rs, i) -> {
            ArticleJournalistEntity articleJournalist = new ArticleJournalistEntity();
            articleJournalist.setId(Pair.of(rs.getLong("articleid"), rs.getLong("journalistid")));
            return articleJournalist;
        }).stream().findFirst();
    }

    @Override
    public Iterable<ArticleJournalistEntity> findAll() {
        String sql = "SELECT * FROM article_journalist";
        return new HashSet<>(jdbcOperations.query(sql, (rs, i) -> {
            ArticleJournalistEntity articleJournalist = new ArticleJournalistEntity();
            articleJournalist.setId(Pair.of(rs.getLong("articleid"), rs.getLong("journalistid")));
            return articleJournalist;
        }));
    }

    @Override
    public Optional<ArticleJournalistEntity> save(ArticleJournalistEntity entity) throws ValidatorException {
        validator.validate(entity);
        String sql = "INSERT INTO article_journalist(articleid, journalistid) VALUES (?, ?)";
        int rows = jdbcOperations.update(sql, entity.getId().getLeft(), entity.getId().getRight());
        if (rows == 1) {
            return Optional.empty();
        } else {
            return Optional.of(entity);
        }
    }

    @Override
    public Optional<ArticleJournalistEntity> delete(Pair<Long, Long> longLongPair) {
        Optional<ArticleJournalistEntity> toBeRemoved = findOne(longLongPair);
        toBeRemoved.ifPresent((articleJournalist) -> jdbcOperations.update("DELETE FROM article_journalist WHERE articleid=? AND journalistid=?", articleJournalist.getId().getLeft(), articleJournalist.getId().getRight()));
        return toBeRemoved;
    }

    @Override
    public Optional<ArticleJournalistEntity> update(ArticleJournalistEntity entity) throws ValidatorException {
        validator.validate(entity);
        int rows = jdbcOperations.update(
                "UPDATE article_journalist SET journalistid=? WHERE articleid=?",
                entity.getId().getRight(),
                entity.getId().getLeft()
        );
        if (rows == 0) {
            return Optional.empty();
        } else {
            return Optional.of(entity);
        }
    }
}
