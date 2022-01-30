package model.statement;

import exceptions.InterpreterException;
import javafx.util.Pair;
import model.programState.ProgramState;
import model.type.IntType;
import model.type.Type;
import model.utils.MyIBarrierTable;
import model.utils.MyIDictionary;
import model.utils.MyIHeap;
import model.value.IntValue;
import model.value.Value;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class AwaitStatement implements IStatement{
    private final String var;
    private static final Lock lock = new ReentrantLock();

    public AwaitStatement(String var) {
        this.var = var;
    }

    @Override
    public ProgramState execute(ProgramState state) throws InterpreterException {
        lock.lock();
        MyIDictionary<String, Value> symTable = state.getSymTable();
        MyIBarrierTable barrierTable = state.getBarrierTable();
        if (symTable.isDefined(var)) {
            IntValue f = (IntValue) symTable.lookUp(var);
            int foundIndex = f.getValue();
            if (barrierTable.containsKey(foundIndex)) {
                Pair<Integer, List<Integer>> foundBarrier = barrierTable.get(foundIndex);
                int NL = foundBarrier.getValue().size();
                int N1 = foundBarrier.getKey();
                ArrayList<Integer> list = (ArrayList<Integer>) foundBarrier.getValue();
                if (N1 > NL) {
                    if (list.contains(state.getId()))
                        state.getExeStack().push(this);
                    else {
                        list.add(state.getId());
                        barrierTable.update(foundIndex, new Pair<>(N1, list));
                        state.setBarrierTable(barrierTable);
                    }
                }
            } else {
                throw new InterpreterException("Index not in Barrier Table!");
            }
        } else {
            throw new InterpreterException("Var is not defined!");
        }
        lock.unlock();
        return null;
    }

    @Override
    public MyIDictionary<String, Type> typeCheck(MyIDictionary<String, Type> typeEnv) throws InterpreterException {
        if (typeEnv.lookUp(var).equals(new IntType()))
            return typeEnv;
        else
            throw new InterpreterException("Var is not of type int!");
    }

    @Override
    public IStatement deepCopy() {
        return new AwaitStatement(var);
    }

    @Override
    public String toString() {
        return String.format("await(%s)", var);
    }
}
