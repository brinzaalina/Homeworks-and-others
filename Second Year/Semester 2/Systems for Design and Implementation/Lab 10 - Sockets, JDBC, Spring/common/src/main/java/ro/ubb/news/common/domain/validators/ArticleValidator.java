package ro.ubb.news.common.domain.validators;

import ro.ubb.news.common.domain.ArticleEntity;
import ro.ubb.news.common.exceptions.ValidatorException;

import java.util.List;

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
