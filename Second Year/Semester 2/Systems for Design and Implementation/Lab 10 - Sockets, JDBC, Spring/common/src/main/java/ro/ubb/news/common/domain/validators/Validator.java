package ro.ubb.news.common.domain.validators;

import ro.ubb.news.common.exceptions.ValidatorException;

public interface Validator<T> {
    void validate(T entity) throws ValidatorException;
}
