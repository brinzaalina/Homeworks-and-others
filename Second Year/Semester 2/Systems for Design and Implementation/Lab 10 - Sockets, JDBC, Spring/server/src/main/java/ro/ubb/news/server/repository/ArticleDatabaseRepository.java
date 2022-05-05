package ro.ubb.news.server.repository;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.jdbc.core.JdbcOperations;
import ro.ubb.news.common.domain.ArticleEntity;
import ro.ubb.news.common.domain.validators.Validator;
import ro.ubb.news.common.exceptions.ValidatorException;

import java.util.HashSet;
import java.util.Optional;

public class ArticleDatabaseRepository implements IRepository<Long, ArticleEntity> {
    @Autowired
    private JdbcOperations jdbcOperations;

    @Autowired
    private Validator<ArticleEntity> validator;

//    public ArticleDatabaseRepository(Validator<ArticleEntity> validator) {
//        this.validator = validator;
//    }

    @Override
    public Optional<ArticleEntity> findOne(Long aLong) {
        String sql = String.format("SELECT * FROM article WHERE id=%d", aLong);
        return jdbcOperations.query(sql, (rs, i) -> {
            Long id = rs.getLong("id");
            String title = rs.getString("title");
            String text = rs.getString("text");
            Long category_id = rs.getLong("category_id");
            ArticleEntity newArticle = new ArticleEntity(title, text, category_id);
            newArticle.setId(id);
            return newArticle;
        }).stream().findFirst();
    }

    @Override
    public Iterable<ArticleEntity> findAll() {
        String sql = "SELECT * FROM article";
        return new HashSet<>(jdbcOperations.query(sql, (rs, i) -> {
            Long id = rs.getLong("id");
            String title = rs.getString("title");
            String text = rs.getString("text");
            Long category_id = rs.getLong("category_id");
            ArticleEntity newArticle = new ArticleEntity(title, text, category_id);
            newArticle.setId(id);
            return newArticle;
        }));
    }

    @Override
    public Optional<ArticleEntity> save(ArticleEntity entity) throws ValidatorException {
        validator.validate(entity);
        String sql = "INSERT INTO article(title, text, category_id) VALUES (?, ?, ?)";
        int rows = jdbcOperations.update(sql, entity.getTitle(), entity.getText(), entity.getCategoryId());
        if (rows == 1) {
            return Optional.empty();
        } else {
            return Optional.of(entity);
        }
    }

    @Override
    public Optional<ArticleEntity> delete(Long aLong) {
        Optional<ArticleEntity> toBeRemoved = findOne(aLong);
        toBeRemoved.ifPresent((category) -> jdbcOperations.update("DELETE FROM article WHERE id=?", category.getId()));
        return toBeRemoved;
    }

    @Override
    public Optional<ArticleEntity> update(ArticleEntity entity) throws ValidatorException {
        validator.validate(entity);
        int rows = jdbcOperations.update(
                "UPDATE article SET title = ?, text = ?, category_id = ? WHERE id = ?",
                entity.getTitle(),
                entity.getText(),
                entity.getCategoryId(),
                entity.getId()
        );
        if (rows == 0) {
            return Optional.empty();
        } else {
            return Optional.of(entity);
        }
    }
}
