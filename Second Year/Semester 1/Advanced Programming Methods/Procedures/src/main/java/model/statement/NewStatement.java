package model.statement;

import exceptions.InterpreterException;
import model.expression.IExpression;
import model.programState.ProgramState;
import model.type.RefType;
import model.type.Type;
import model.utils.MyIDictionary;
import model.utils.MyIHeap;
import model.utils.MyIStack;
import model.value.RefValue;
import model.value.Value;

public class NewStatement implements IStatement{
    private final String varName;
    private final IExpression expression;

    public NewStatement(String varName, IExpression expression) {
        this.varName = varName;
        this.expression = expression;
    }

    @Override
    public ProgramState execute(ProgramState state) throws InterpreterException {
        MyIStack<MyIDictionary<String, Value>> symTable = state.getSymTable();
        MyIDictionary<String, Value> currentSymbolTable = symTable.peek();

        MyIHeap heap = state.getHeap();
        if (currentSymbolTable.isDefined(varName)) {
            Value varValue = currentSymbolTable.lookUp(varName);
            if ((varValue.getType() instanceof RefType)) {
                Value evaluated = expression.eval(currentSymbolTable, heap);
                Type locationType = ((RefValue) varValue).getLocationType();
                if (locationType.equals(evaluated.getType())) {
                    int newPosition = heap.add(evaluated);
                    currentSymbolTable.put(varName, new RefValue(newPosition, locationType));
                    state.setSymTable(symTable);
                    state.setHeap(heap);
                } else
                    throw new InterpreterException(String.format("%s not of %s", varName, evaluated.getType()));
            } else {
                throw new InterpreterException(String.format("%s in not of RefType", varName));
            }
        } else {
            throw new InterpreterException(String.format("%s not in symTable", varName));
        }
        return null;
    }

    @Override
    public MyIDictionary<String, Type> typeCheck(MyIDictionary<String, Type> typeEnv) throws InterpreterException {
        Type typeVar = typeEnv.lookUp(varName);
        Type typeExpr = expression.typeCheck(typeEnv);
        if (typeVar.equals(new RefType(typeExpr)))
            return typeEnv;
        else
            throw new InterpreterException("NEW statement: right hand side and left hand side have different types.");
    }

    @Override
    public IStatement deepCopy() {
        return new NewStatement(varName, expression.deepCopy());
    }

    @Override
    public String toString() {
        return String.format("New(%s, %s)", varName, expression);
    }
}
