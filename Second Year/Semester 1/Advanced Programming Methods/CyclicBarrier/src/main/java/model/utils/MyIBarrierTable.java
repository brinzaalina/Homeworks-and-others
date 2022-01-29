package model.utils;

import javafx.util.Pair;

import java.util.HashMap;
import java.util.List;

public interface MyIBarrierTable {
    void put(int key, Pair<Integer, List<Integer>> value);
    Pair<Integer, List<Integer>> get(int key);
    boolean containsKey(int key);
    int getFreeAddress();
    void setFreeAddress(int freeAddress);
    void update(int key, Pair<Integer, List<Integer>> value);
    HashMap<Integer, Pair<Integer, List<Integer>>> getBarrierTable();
    void setBarrierTable(HashMap<Integer, Pair<Integer, List<Integer>>> newBarrierTable);
}
