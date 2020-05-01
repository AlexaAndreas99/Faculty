package Model.ADT;

import java.util.ArrayList;
import java.util.List;

public class MyList<T> implements MyIList<T> {
    private List<T> list;

    @Override
    public String toString() {
        return list.toString();
    }

    public MyList() {
        this.list = new ArrayList<T>();
    }

    @Override
    public void add(T v) {
        this.list.add(v);
    }

    @Override
    public void remove(T v) {
        this.list.remove(v);
    }

    @Override
    public int size() {
        return this.list.size();
    }
}
