package ro.ubb.news.server.repository;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.jdbc.core.JdbcOperations;
import ro.ubb.news.common.domain.CategoryEntity;
import ro.ubb.news.common.domain.validators.Validator;
import ro.ubb.news.common.exceptions.ValidatorException;

import java.util.HashSet;
import java.util.Optional;

public class CategoryDatabaseRepository implements IRepository<Long, CategoryEntity> {
    @Autowired
    private JdbcOperations jdbcOperations;

    @Autowired
    private Validator<CategoryEntity> validator;

//    public CategoryDatabaseRepository(Validator<CategoryEntity> validator) {
//        this.validator = validator;
//    }

    @Override
    public Optional<CategoryEntity> findOne(Long aLong) {
        String sql = String.format("SELECT * FROM category WHERE id=%d", aLong);
        return jdbcOperations.query(sql, (rs, i) -> {
            Long id = rs.getLong("id");
            String name = rs.getString("name");
            CategoryEntity newCategory = new CategoryEntity(name);
            newCategory.setId(id);
            return newCategory;
        }).stream().findFirst();
    }

    @Override
    public Iterable<CategoryEntity> findAll() {
        String sql = "SELECT * FROM category";
        return new HashSet<>(jdbcOperations.query(sql, (rs, i) -> {
            Long id = rs.getLong("id");
            String name = rs.getString("name");
            CategoryEntity newCategory = new CategoryEntity(name);
            newCategory.setId(id);
            return newCategory;
        }));
    }

    @Override
    public Optional<CategoryEntity> save(CategoryEntity entity) throws ValidatorException {
        validator.validate(entity);
        String sql = "INSERT INTO category(name) VALUES (?)";
        int rows = jdbcOperations.update(sql, entity.getName());
        if (rows == 1) {
            return Optional.empty();
        } else {
            return Optional.of(entity);
        }
    }

    @Override
    public Optional<CategoryEntity> delete(Long aLong) {
        Optional<CategoryEntity> toBeRemoved = findOne(aLong);
        toBeRemoved.ifPresent((category) -> jdbcOperations.update("DELETE FROM category WHERE id=?", category.getId()));
        return toBeRemoved;
    }

    @Override
    public Optional<CategoryEntity> update(CategoryEntity entity) throws ValidatorException {
        validator.validate(entity);
        int rows = jdbcOperations.update(
                "UPDATE category SET name = ? WHERE id = ?",
                entity.getName(),
                entity.getId()
        );
        if (rows == 0) {
            return Optional.empty();
        } else {
            return Optional.of(entity);
        }
    }
}
