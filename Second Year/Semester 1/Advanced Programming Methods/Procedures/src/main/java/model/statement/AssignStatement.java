package model.statement;

import exceptions.InterpreterException;
import model.expression.IExpression;
import model.programState.ProgramState;
import model.type.Type;
import model.utils.MyIDictionary;
import model.utils.MyIStack;
import model.value.Value;

public class AssignStatement implements IStatement {
    private final String key;
    private final IExpression expression;

    public AssignStatement(String key, IExpression expression) {
        this.key = key;
        this.expression = expression;
    }

    @Override
    public ProgramState execute(ProgramState state) throws InterpreterException {
        MyIStack<MyIDictionary<String, Value>> symbolTable = state.getSymTable();
        MyIDictionary<String, Value> currentSymbolTable = symbolTable.peek();

        if (currentSymbolTable.isDefined(key)) {
            Value value = expression.eval(currentSymbolTable, state.getHeap());
            Type typeId = (currentSymbolTable.lookUp(key)).getType();
            if (value.getType().equals(typeId)) {
                currentSymbolTable.update(key, value);
            } else {
                throw new InterpreterException("Declared type of variable " + key + " and type of the assigned expression do not match.");
            }
        } else {
            throw new InterpreterException("The used variable " + key + " was not declared before.");
        }

        state.setSymTable(symbolTable);
        return null;
    }

    @Override
    public MyIDictionary<String, Type> typeCheck(MyIDictionary<String, Type> typeEnv) throws InterpreterException {
        Type typeVar =  typeEnv.lookUp(key);
        Type typeExpr = expression.typeCheck(typeEnv);
        if (typeVar.equals(typeExpr))
            return typeEnv;
        else
            throw new InterpreterException("Assignment: right hand side and left hand side have different types.");
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
