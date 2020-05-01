package Model.ADT;

import Model.Values.Value;

import java.util.*;

public interface MyIDictionary<K,V> {

    void add(K key,V value);
    void remove(K key);
    public boolean isDefined(K key);
    public V getValue(K key);
    public void update(K key,V value);
    public void setDict(Map<K, V> map);
    public List<V> getValues();
    public List<K> getKeys();
    public Iterable<K> getElements();
    public Map<K, V> getDict();


    int size();

    Set<Map.Entry<K, V>> getEntrySet();
}
