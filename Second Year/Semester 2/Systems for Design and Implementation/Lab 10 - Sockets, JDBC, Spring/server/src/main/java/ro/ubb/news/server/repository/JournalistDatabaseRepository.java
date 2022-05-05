package ro.ubb.news.server.repository;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.jdbc.core.JdbcOperations;
import ro.ubb.news.common.domain.JournalistEntity;
import ro.ubb.news.common.domain.UserEntity;
import ro.ubb.news.common.domain.validators.Validator;
import ro.ubb.news.common.exceptions.ValidatorException;

import java.util.Date;
import java.util.HashSet;
import java.util.Optional;

public class JournalistDatabaseRepository implements IRepository<Long, JournalistEntity> {
    @Autowired
    private JdbcOperations jdbcOperations;

    @Autowired
    private Validator<JournalistEntity> validator;

//    public JournalistDatabaseRepository(Validator<JournalistEntity> validator) {
//        this.validator = validator;
//    }

    @Override
    public Optional<JournalistEntity> findOne(Long aLong) {
        String sql = String.format("SELECT * FROM journalist WHERE id=%d", aLong);
        return jdbcOperations.query(sql, (rs, i) -> {
            Long id = rs.getLong("id");
            return new JournalistEntity(id);
        }).stream().findFirst();
    }

    @Override
    public Iterable<JournalistEntity> findAll() {
        String sql = "SELECT * FROM journalist";
        return new HashSet<>(jdbcOperations.query(sql, (rs, i) -> {
            Long id = rs.getLong("id");
            return new JournalistEntity(id);
        }));
    }

    @Override
    public Optional<JournalistEntity> save(JournalistEntity entity) throws ValidatorException {
        validator.validate(entity);
        String sql = "INSERT INTO journalist(id) VALUES (?)";
        int rows = jdbcOperations.update(sql, entity.getId());
        if (rows == 1) {
            return Optional.empty();
        } else {
            return Optional.of(entity);
        }
    }

    @Override
    public Optional<JournalistEntity> delete(Long aLong) {
        Optional<JournalistEntity> toBeRemoved = findOne(aLong);
        toBeRemoved.ifPresent((journalist) -> jdbcOperations.update("DELETE FROM journalist WHERE id=?", journalist.getId()));
        return toBeRemoved;
    }

    @Override
    public Optional<JournalistEntity> update(JournalistEntity entity) throws ValidatorException {
        this.validator.validate(entity);
        return Optional.of(entity);
    }
}
