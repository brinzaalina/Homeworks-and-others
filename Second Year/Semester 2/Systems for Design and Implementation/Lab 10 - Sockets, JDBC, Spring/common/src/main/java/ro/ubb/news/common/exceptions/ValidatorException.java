package ro.ubb.news.common.exceptions;

public class ValidatorException extends NewsServiceException{
    public ValidatorException(String message) {
        super(message);
    }

    public ValidatorException(String message, Throwable cause) {
        super(message, cause);
    }
}
