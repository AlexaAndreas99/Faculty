package Model.ADT;

import Model.Values.Value;

import java.util.Dictionary;
import java.util.Hashtable;

public class MyHeap implements MyIHeap {
    private Dictionary<Integer, Value> dict;
    private static int free=0;

    public MyHeap() {
        this.dict=new Hashtable<Integer, Value>();
    }

    public int add(Value value) {
        free++;
        this.dict.put(free,value);
        return free;
    }


    public void remove(Integer key) {

    }


    public boolean isDefined(Integer key) {
        return false;
    }


    public Value getValue(Integer key) {
        return null;
    }


    public void update(Integer key, Value value) {

    }


    public int size() {
        return 0;
    }
}
