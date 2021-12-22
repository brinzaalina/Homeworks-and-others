package exceptions;

public class ExpressionEvaluationException extends Exception{
    public ExpressionEvaluationException() {
        super();
    }

    public ExpressionEvaluationException(String message) {
        super(message);
    }
}
