package ro.ubb.news.common.domain.validators;

import ro.ubb.news.common.domain.UserEntity;
import ro.ubb.news.common.exceptions.ValidatorException;

import java.util.Date;
import java.util.List;

public class UserValidator implements Validator<UserEntity> {
    @Override
    public void validate(UserEntity entity) throws ValidatorException {
        List<UserEntity> userEntityList = List.of(entity);
        userEntityList.stream()
                .filter(e -> e.getLastName().length() < 80)
                .filter(e -> e.getFirstName().length() < 80)
                .filter(e -> e.getDob().before(new Date()))
                .findFirst()
                .orElseThrow(() -> new ValidatorException("Validation fail"));
    }
}
