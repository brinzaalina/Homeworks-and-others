package model.expression;

import exceptions.ADTException;
import exceptions.ExpressionEvaluationException;
import model.type.Type;
import model.utils.MyIDictionary;
import model.utils.MyIHeap;
import model.value.Value;

public interface IExpression {
    Type typeCheck(MyIDictionary<String, Type> typeEnv) throws ExpressionEvaluationException, ADTException;
    Value eval(MyIDictionary<String, Value> table, MyIHeap heap) throws ExpressionEvaluationException, ADTException;
    IExpression deepCopy();
}
