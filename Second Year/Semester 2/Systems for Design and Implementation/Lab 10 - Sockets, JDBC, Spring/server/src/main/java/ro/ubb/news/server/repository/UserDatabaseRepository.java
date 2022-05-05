package ro.ubb.news.server.repository;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.jdbc.core.JdbcOperations;
import ro.ubb.news.common.domain.UserEntity;
import ro.ubb.news.common.domain.validators.Validator;
import ro.ubb.news.common.exceptions.ValidatorException;

import java.util.Date;
import java.util.HashSet;
import java.util.Optional;

public class UserDatabaseRepository implements IRepository<Long, UserEntity> {
    @Autowired
    private JdbcOperations jdbcOperations;

    @Autowired
    private Validator<UserEntity> validator;

//    public UserDatabaseRepository(Validator<UserEntity> validator) {
//        this.validator = validator;
//    }

    @Override
    public Optional<UserEntity> findOne(Long aLong) {
        String sql = String.format("SELECT * FROM app_user WHERE id=%d", aLong);
        return jdbcOperations.query(sql, (rs, i) -> {
            Long id = rs.getLong("id");
            String lastName = rs.getString("last_name");
            String firstName = rs.getString("first_name");
            String email = rs.getString("email");
            Date dob = rs.getDate("dob");
            UserEntity newUser = new UserEntity(lastName, firstName, email);
            newUser.setId(id);
            newUser.setDob(dob);
            return newUser;
        }).stream().findFirst();
    }

    @Override
    public Iterable<UserEntity> findAll() {
        String sql = "SELECT * FROM app_user";
        return new HashSet<>(jdbcOperations.query(sql, (rs, i) -> {
            Long id = rs.getLong("id");
            String lastName = rs.getString("last_name");
            String firstName = rs.getString("first_name");
            String email = rs.getString("email");
            Date dob = rs.getDate("dob");
            UserEntity newUser = new UserEntity(lastName, firstName, email);
            newUser.setId(id);
            newUser.setDob(dob);
            return newUser;
        }));
    }

    @Override
    public Optional<UserEntity> save(UserEntity entity) throws ValidatorException {
        validator.validate(entity);
        String sql = "INSERT INTO app_user(last_name, first_name, email, dob) VALUES (?,?,?,?)";
        int rows = jdbcOperations.update(sql, entity.getLastName(), entity.getFirstName(), entity.getEmail(), entity.getDob());
        if (rows == 1) {
            return Optional.empty();
        } else {
            return Optional.of(entity);
        }
    }

    @Override
    public Optional<UserEntity> delete(Long aLong) {
        Optional<UserEntity> toBeRemoved = findOne(aLong);
        toBeRemoved.ifPresent((user) -> jdbcOperations.update("DELETE FROM app_user WHERE id=?", user.getId()));
        return toBeRemoved;
    }

    @Override
    public Optional<UserEntity> update(UserEntity entity) throws ValidatorException {
        validator.validate(entity);
        int rows = jdbcOperations.update(
                "UPDATE app_user SET last_name = ?, first_name = ?, email = ?, dob = ? WHERE id = ?",
                entity.getLastName(),
                entity.getFirstName(),
                entity.getEmail(),
                entity.getDob(),
                entity.getId()
        );
        if (rows == 0) {
            return Optional.empty();
        } else {
            return Optional.of(entity);
        }
    }
}
