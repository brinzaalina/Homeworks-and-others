package ro.ubb.news.common.domain.validators;

import ro.ubb.news.common.domain.CategoryEntity;
import ro.ubb.news.common.exceptions.ValidatorException;

import java.util.List;

public class CategoryValidator implements Validator<CategoryEntity> {
    @Override
    public void validate(CategoryEntity entity) throws ValidatorException {
        List<CategoryEntity> categoryEntityList = List.of(entity);
        categoryEntityList.stream()
                .filter(e -> e.getName().length() <= 50)
                .findFirst()
                .orElseThrow(() -> new ValidatorException("Validation fail"));
    }
}
