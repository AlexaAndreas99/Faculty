package Model.ADT;

import java.util.Stack;

public class MyStack<T> implements MyIStack<T> {


    private Stack<T> stack;

    @Override
    public String toString() {
        return stack.toString();
    }

    public MyStack() {
        this.stack = new Stack<T>();
    }

    @Override
    public T pop() {
        return this.stack.pop();
    }

    @Override
    public void push(T v) {
        this.stack.push(v);
    }

    @Override
    public int size() {
        return this.stack.size();
    }

    @Override
    public boolean isEmpty() {
        return this.stack.size()==0;
    }
}
