package model.utils;

import exceptions.InterpreterException;

import java.util.HashMap;
import java.util.List;

public interface MyIToySemaphoreTable {
    void put(int key, Tuple<Integer, List<Integer>, Integer> value) throws InterpreterException;
    Tuple<Integer, List<Integer>, Integer> get(int key) throws InterpreterException;
    boolean containsKey(int key);
    int getFreeAddress();
    void setFreeAddress(int freeAddress);
    void update(int key, Tuple<Integer, List<Integer>, Integer> value) throws InterpreterException;
    HashMap<Integer, Tuple<Integer, List<Integer>, Integer>> getToySemaphoreTable();
    void setToySemaphoreTable(HashMap<Integer, Tuple<Integer, List<Integer>, Integer>> newToySemaphoreTable);
}
