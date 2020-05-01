package Model.ADT;

public interface MyIStack<T> {
    T pop();
    void push(T v);
    int size();
    boolean isEmpty();

}
