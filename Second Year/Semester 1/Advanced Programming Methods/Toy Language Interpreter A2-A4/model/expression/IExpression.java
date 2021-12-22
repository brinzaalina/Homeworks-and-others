package model.expression;

import exceptions.ADTException;
import exceptions.ExpressionEvaluationException;
import model.utils.MyIDictionary;
import model.utils.MyIHeap;
import model.value.Value;

public interface IExpression {
    Value eval(MyIDictionary<String, Value> symTable, MyIHeap heap) throws ExpressionEvaluationException, ADTException;
    IExpression deepCopy();
}
