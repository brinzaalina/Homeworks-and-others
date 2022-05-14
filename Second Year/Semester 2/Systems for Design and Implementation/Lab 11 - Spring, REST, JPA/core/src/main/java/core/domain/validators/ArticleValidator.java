package core.domain.validators;

import core.domain.ArticleEntity;
import core.exceptions.ValidatorException;
import org.springframework.stereotype.Component;

import java.util.List;

@Component
public class ArticleValidator implements Validator<ArticleEntity> {
    @Override
    public void validate(ArticleEntity entity) throws ValidatorException {
        List<ArticleEntity> articleEntityList = List.of(entity);
        articleEntityList.stream()
                .filter(e -> e.getTitle().length() <= 80)
                .filter(e -> e.getText().length() <= 500)
                .findFirst()
                .orElseThrow(() -> new ValidatorException("Validation fail"));
    }
}
