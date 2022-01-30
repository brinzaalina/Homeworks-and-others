package model.utils;

import exceptions.InterpreterException;
import javafx.util.Pair;
import model.statement.IStatement;

import java.util.Collection;
import java.util.HashMap;
import java.util.List;
import java.util.Set;

public class MyProcTable implements MyIProcTable{
    private HashMap<String,  Pair<List<String>, IStatement>> procTable;

    public MyProcTable() {
        this.procTable = new HashMap<>();
    }

    @Override
    public boolean isDefined(String key) {
        synchronized (this) {
            return this.procTable.containsKey(key);
        }
    }

    @Override
    public void put(String key, Pair<List<String>, IStatement> value) {
        synchronized (this) {
            this.procTable.put(key, value);
        }
    }

    @Override
    public Pair<List<String>, IStatement> lookUp(String key) throws InterpreterException {
        synchronized (this) {
            if (!isDefined(key))
                throw new InterpreterException(key + " is not defined.");
            return this.procTable.get(key);
        }
    }

    @Override
    public void update(String key, Pair<List<String>, IStatement> value) throws InterpreterException {
        synchronized (this) {
            if (!isDefined(key))
                throw new InterpreterException(key + " is not defined.");
            this.procTable.put(key, value);
        }
    }

    @Override
    public Collection<Pair<List<String>, IStatement>> values() {
        synchronized (this) {
            return this.procTable.values();
        }
    }

    @Override
    public void remove(String key) throws InterpreterException {
        synchronized (this) {
            if (!isDefined(key))
                throw new InterpreterException(key + " is not defined.");
            this.procTable.remove(key);
        }
    }

    @Override
    public Set<String> keySet() {
        synchronized (this) {
            return procTable.keySet();
        }
    }

    @Override
    public HashMap<String, Pair<List<String>, IStatement>> getContent() {
        synchronized (this) {
            return procTable;
        }
    }

    @Override
    public MyIDictionary<String, Pair<List<String>, IStatement>> deepCopy() throws InterpreterException {
        MyIDictionary<String, Pair<List<String>, IStatement>> toReturn = new MyDictionary<>();
        for (String key: keySet())
            try {
                toReturn.put(key, lookUp(key));
            } catch (InterpreterException e) {
                throw new InterpreterException(e.getMessage());
            }
        return toReturn;
    }

    @Override
    public String toString() {
        return procTable.toString();
    }
}
