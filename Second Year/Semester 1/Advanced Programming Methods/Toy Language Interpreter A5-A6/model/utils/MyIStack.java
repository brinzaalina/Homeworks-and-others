package model.utils;

import exceptions.ADTException;

import java.util.List;

public interface MyIStack<T> {
    T pop() throws ADTException;
    void push(T element);
    T peek();
    boolean isEmpty();
    List<T> getReversed();
}
