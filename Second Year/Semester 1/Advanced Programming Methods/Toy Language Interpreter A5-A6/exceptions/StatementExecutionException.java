package exceptions;

public class StatementExecutionException extends Exception{
    public StatementExecutionException() {
        super();
    }

    public StatementExecutionException(String message) {
        super(message);
    }
}
