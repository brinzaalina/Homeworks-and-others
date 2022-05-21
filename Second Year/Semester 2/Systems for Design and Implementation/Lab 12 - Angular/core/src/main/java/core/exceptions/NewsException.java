package core.exceptions;

public class NewsException extends RuntimeException{
    public NewsException(String message) {
        super(message);
    }

    public NewsException(String message, Throwable cause) {
        super(message, cause);
    }
}
