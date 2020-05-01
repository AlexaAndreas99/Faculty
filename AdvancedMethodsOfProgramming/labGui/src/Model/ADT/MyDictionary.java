package Model.ADT;

import Model.ADT.MyIDictionary;
import Model.Values.Value;

import java.util.*;
import java.util.stream.Collectors;

public class MyDictionary<K ,V> implements MyIDictionary<K,V> {
    //private Dictionary<K,V> dict;
    private Map<K, V> dict;

    @Override
    public List<K> getKeys() {
        return null;
    }

    public Map<K, V> getDict() {
        return dict;
    }

    @Override
    public List<V> getValues() {
        return new LinkedList<>(this.dict.values());
    }

    @Override
    public Set<Map.Entry<K, V>> getEntrySet() {
        return this.dict.entrySet();
    }


    @Override
    public Iterable<K> getElements() {
        return dict.keySet();
    }

    public void setDict(Map<K, V> map) {
        // Enumeration<K> e=Collections.enumeration(map.keySet());
        //List<K> keys=Collections.list(e);
        //Dictionary<K,V> dictcopy=keys.stream().collect(Collectors.t)
        this.dict = map;
    }

    @Override
    public String toString() {
        return dict.toString();
    }

    public MyDictionary() {
        //this.dict = new Hashtable<K,V>();
        this.dict = new HashMap<>();
    }

    @Override
    public void add(K key, V value) {
        this.dict.put(key, value);
    }

    @Override
    public void remove(K key) {
        this.dict.remove(key);

    }

    @Override
    public V getValue(K key) {
        return this.dict.get(key);
    }

    @Override
    public void update(K key, V value) {
        //this.dict.remove(key);
        this.dict.put(key, value);
    }

    @Override
    public boolean isDefined(K key) {
        return this.dict.get(key) != null;
    }

    @Override
    public int size() {
        return this.dict.size();
    }

    @Override
    public Iterable<Map.Entry<K, V>> getAll() {
        return dict.entrySet();
    }
}
