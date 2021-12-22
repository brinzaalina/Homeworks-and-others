package model.utils;

import exceptions.ADTException;

import java.util.List;
import java.util.function.Consumer;

public interface MyIList<T> {
    void add(T elem);
    T pop() throws ADTException;
    boolean isEmpty();
    List<T> getList();
}
