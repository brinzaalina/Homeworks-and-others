package model.statement;

import exceptions.ADTException;
import exceptions.ExpressionEvaluationException;
import exceptions.StatementExecutionException;
import model.expression.IExpression;
import model.programState.ProgramState;
import model.type.Type;
import model.utils.MyIDictionary;
import model.value.Value;

public class AssignStatement implements IStatement {
    private final String key;
    private final IExpression expression;

    public AssignStatement(String key, IExpression expression) {
        this.key = key;
        this.expression = expression;
    }

    @Override
    public ProgramState execute(ProgramState state) throws StatementExecutionException, ExpressionEvaluationException, ADTException {
        MyIDictionary<String, Value> symbolTable = state.getSymTable();

            if (symbolTable.isDefined(key)) {
                Value value = expression.eval(symbolTable, state.getHeap());
                Type typeId = (symbolTable.lookUp(key)).getType();
                if (value.getType().equals(typeId)) {
                    symbolTable.update(key, value);
                } else {
                    throw new StatementExecutionException("Declared type of variable " + key + " and type of the assigned expression do not match.");
                }
            } else {
                throw new StatementExecutionException("The used variable " + key + " was not declared before.");
            }
        state.setSymTable(symbolTable);
        return state;
    }

    @Override
    public IStatement deepCopy() {
        return new AssignStatement(key, expression.deepCopy());
    }

    @Override
    public String toString() {
        return String.format("%s = %s", key, expression.toString());
    }
}
