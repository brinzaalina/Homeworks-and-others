package model.expression;

import exceptions.InterpreterException;
import model.type.IntType;
import model.type.Type;
import model.utils.MyIDictionary;
import model.utils.MyIHeap;
import model.value.Value;

public class MULExpression implements IExpression{
    private final IExpression expression1;
    private final IExpression expression2;

    public MULExpression(IExpression expression1, IExpression expression2) {
        this.expression1 = expression1;
        this.expression2 = expression2;
    }

    @Override
    public Type typeCheck(MyIDictionary<String, Type> typeEnv) throws InterpreterException {
        Type type1 = expression1.typeCheck(typeEnv);
        Type type2 = expression2.typeCheck(typeEnv);
        if (type1.equals(new IntType()) && type2.equals(new IntType()))
            return new IntType();
        else
            throw new InterpreterException("Expressions in the MUL should be int!");
    }

    @Override
    public Value eval(MyIDictionary<String, Value> table, MyIHeap heap) throws InterpreterException {
        IExpression converted = new ArithmeticExpression('-',
                new ArithmeticExpression('*', expression1, expression2),
                new ArithmeticExpression('+', expression1, expression2));
        return converted.eval(table, heap);
    }

    @Override
    public IExpression deepCopy() {
        return new MULExpression(expression1.deepCopy(), expression2.deepCopy());
    }

    @Override
    public String toString() {
        return String.format("MUL(%s, %s)", expression1, expression2);
    }
}
