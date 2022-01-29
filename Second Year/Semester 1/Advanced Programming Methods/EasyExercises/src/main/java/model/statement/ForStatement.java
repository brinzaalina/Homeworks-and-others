package model.statement;

import exceptions.InterpreterException;
import model.expression.IExpression;
import model.expression.RelationalExpression;
import model.expression.VariableExpression;
import model.programState.ProgramState;
import model.type.IntType;
import model.type.Type;
import model.utils.MyIDictionary;
import model.utils.MyIStack;

public class ForStatement implements IStatement{
    private final IExpression expression1;
    private final IExpression expression2;
    private final IExpression expression3;
    private final IStatement statement;

    public ForStatement(IExpression expression1, IExpression expression2, IExpression expression3, IStatement statement) {
        this.expression1 = expression1;
        this.expression2 = expression2;
        this.expression3 = expression3;
        this.statement = statement;
    }

    @Override
    public ProgramState execute(ProgramState state) throws InterpreterException {
        MyIStack<IStatement> exeStack = state.getExeStack();
        IStatement converted = new CompoundStatement(new AssignStatement("v", expression1),
                new WhileStatement(new RelationalExpression("<", new VariableExpression("v"), expression2),
                        new CompoundStatement(statement, new AssignStatement("v", expression3))));
        exeStack.push(converted);
        state.setExeStack(exeStack);
        return null;
    }

    @Override
    public MyIDictionary<String, Type> typeCheck(MyIDictionary<String, Type> typeEnv) throws InterpreterException {
        Type type1 = expression1.typeCheck(typeEnv);
        Type type2 = expression2.typeCheck(typeEnv);
        Type type3 = expression3.typeCheck(typeEnv);

        if (type1.equals(new IntType()) && type2.equals(new IntType()) && type3.equals(new IntType()))
            return typeEnv;
        else
            throw new InterpreterException("The for statement is invalid!");
    }

    @Override
    public IStatement deepCopy() {
        return new ForStatement(expression1.deepCopy(), expression2.deepCopy(), expression3.deepCopy(), statement.deepCopy());
    }

    @Override
    public String toString() {
        return String.format("for(v=%s; v<%s; v=%s) {%s}", expression1, expression2, expression3, statement);
    }
}
