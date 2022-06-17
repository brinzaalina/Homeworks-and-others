package core.domain.validators;

import core.domain.JournalistEntity;
import core.exceptions.ValidatorException;
import org.springframework.stereotype.Component;

import java.util.Date;
import java.util.List;

@Component
public class JournalistValidator implements Validator<JournalistEntity> {
    @Override
    public void validate(JournalistEntity entity) throws ValidatorException {
        List<JournalistEntity> journalistEntities = List.of(entity);
        journalistEntities.stream()
                .filter(e -> e.getLastName().length() < 80)
                .filter(e -> e.getFirstName().length() < 80)
                .filter(e -> e.getDob().before(new Date()))
                .findFirst()
                .orElseThrow(() -> new ValidatorException("Validation fail"));
    }
}
