package core.domain.validators;

import core.domain.ArticleJournalistEntity;
import core.exceptions.ValidatorException;
import org.springframework.stereotype.Component;

@Component
public class ArticleJournalistValidator implements Validator<ArticleJournalistEntity> {
    @Override
    public void validate(ArticleJournalistEntity entity) throws ValidatorException {

    }
}
