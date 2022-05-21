package core.domain.validators;

import core.domain.CategoryEntity;
import core.exceptions.ValidatorException;
import org.springframework.stereotype.Component;

import java.util.List;

@Component
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
