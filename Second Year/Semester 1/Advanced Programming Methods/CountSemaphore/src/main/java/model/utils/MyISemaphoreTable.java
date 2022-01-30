package model.utils;

import exceptions.InterpreterException;
import javafx.util.Pair;

import java.util.HashMap;
import java.util.List;

public interface MyISemaphoreTable {
    void put(int key, Pair<Integer, List<Integer>> value) throws InterpreterException;
    Pair<Integer, List<Integer>> get(int key) throws InterpreterException;
    boolean containsKey(int key);
    int getFreeAddress();
    void setFreeAddress(int freeAddress);
    void update(int key, Pair<Integer, List<Integer>> value) throws InterpreterException;
    HashMap<Integer, Pair<Integer, List<Integer>>> getSemaphoreTable();
    void setSemaphoreTable(HashMap<Integer, Pair<Integer, List<Integer>>> newSemaphoreTable);
}
