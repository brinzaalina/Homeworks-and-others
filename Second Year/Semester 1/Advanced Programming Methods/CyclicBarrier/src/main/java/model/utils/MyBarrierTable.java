package model.utils;

import javafx.util.Pair;

import java.util.HashMap;
import java.util.List;

public class MyBarrierTable implements MyIBarrierTable{
    private HashMap<Integer, Pair<Integer, List<Integer>>> barrierTable;
    private int freeLocation = 0;

    public MyBarrierTable() {
        this.barrierTable = new HashMap<>();
    }

    public MyBarrierTable(HashMap<Integer, Pair<Integer, List<Integer>>> barrierTable) {
        this.barrierTable = barrierTable;
    }

    @Override
    public void put(int key, Pair<Integer, List<Integer>> value) {
        synchronized (this) {
            barrierTable.put(key, value);
        }
    }

    @Override
    public Pair<Integer, List<Integer>> get(int key) {
        synchronized (this) {
            return barrierTable.get(key);
        }
    }

    @Override
    public boolean containsKey(int key) {
        synchronized (this) {
            return barrierTable.containsKey(key);
        }
    }

    @Override
    public int getFreeAddress() {
        synchronized (this) {
            freeLocation++;
            return freeLocation;
        }
    }

    @Override
    public void setFreeAddress(int freeAddress) {
        synchronized (this) {
            this.freeLocation = freeAddress;
        }
    }

    @Override
    public void update(int key, Pair<Integer, List<Integer>> value) {
        synchronized (this) {
            barrierTable.replace(key, value);
        }
    }

    @Override
    public HashMap<Integer, Pair<Integer, List<Integer>>> getBarrierTable() {
        synchronized (this) {
            return barrierTable;
        }
    }

    @Override
    public void setBarrierTable(HashMap<Integer, Pair<Integer, List<Integer>>> newBarrierTable) {
        synchronized (this) {
            this.barrierTable = newBarrierTable;
        }
    }

    @Override
    public String toString() {
        return this.barrierTable.toString();
    }
}
