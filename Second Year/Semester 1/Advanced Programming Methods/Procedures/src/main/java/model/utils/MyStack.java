package model.utils;

import exceptions.InterpreterException;

import java.util.Arrays;
import java.util.Collections;
import java.util.List;
import java.util.Stack;

public class MyStack<T> implements MyIStack<T> {
    Stack<T> stack;

    public MyStack() {
        this.stack = new Stack<>();
    }

    public MyStack(Stack<T> stack) {
        this.stack = stack;
    }

    @Override
    public T pop() throws InterpreterException {
        if (stack.isEmpty())
            throw new InterpreterException("Stack is empty!");
        return this.stack.pop();
    }

    @Override
    public void push(T element) {
        this.stack.push(element);
    }

    @Override
    public String toString() {
        return this.stack.toString();
    }

    @Override
    public T peek() throws InterpreterException {
        if (stack.isEmpty())
            throw new InterpreterException("Stack is empty!");
        return this.stack.peek();
    }

    @Override
    public boolean isEmpty() {
        return this.stack.isEmpty();
    }

    @Override
    public List<T> getReversed() {
        List<T> list = Arrays.asList((T[]) stack.toArray());
        Collections.reverse(list);
        return list;
    }

    @Override
    public MyIStack<T> clone() {
        return new MyStack<T>((Stack<T>)stack.clone());
    }
}
