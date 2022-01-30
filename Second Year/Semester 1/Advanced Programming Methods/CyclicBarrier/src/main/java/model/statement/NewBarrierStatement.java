package model.statement;

import exceptions.InterpreterException;
import javafx.util.Pair;
import model.expression.IExpression;
import model.programState.ProgramState;
import model.type.IntType;
import model.type.Type;
import model.utils.MyIBarrierTable;
import model.utils.MyIDictionary;
import model.utils.MyIHeap;
import model.value.IntValue;
import model.value.Value;

import java.util.ArrayList;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class NewBarrierStatement implements IStatement{
    private final String var;
    private final IExpression expression;
    private static final Lock lock = new ReentrantLock();

    public NewBarrierStatement(String var, IExpression expression) {
        this.var = var;
        this.expression = expression;
    }
    @Override
    public ProgramState execute(ProgramState state) throws InterpreterException {
        lock.lock();
        MyIDictionary<String, Value> symTable = state.getSymTable();
        MyIHeap heap = state.getHeap();
        MyIBarrierTable barrierTable = state.getBarrierTable();
        IntValue number = (IntValue) (expression.eval(symTable, heap));
        int nr = number.getValue();
        int freeAddress = barrierTable.getFreeAddress();
        barrierTable.put(freeAddress, new Pair<>(nr, new ArrayList<>()));
        if (symTable.isDefined(var))
            symTable.update(var, new IntValue(freeAddress));
        else
            throw new InterpreterException(String.format("%s is not defined in the symbol table!", var));
        lock.unlock();
        return null;
    }

    @Override
    public MyIDictionary<String, Type> typeCheck(MyIDictionary<String, Type> typeEnv) throws InterpreterException {
        if (typeEnv.lookUp(var).equals(new IntType()))
            if (expression.typeCheck(typeEnv).equals(new IntType()))
                return typeEnv;
            else
                throw new InterpreterException("Expression is not of type int!");
        else
            throw new InterpreterException("Variable is not of type int!");
    }

    @Override
    public IStatement deepCopy() {
        return new NewBarrierStatement(var, expression.deepCopy());
    }

    @Override
    public String toString() {
        return String.format("newBarrier(%s, %s)", var, expression);
    }
}
