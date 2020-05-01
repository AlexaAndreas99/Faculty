package Repository;

import Model.Automobile;
import Exception.AutoException;
public interface Container {
    void add(Automobile a)throws AutoException;
    void remove(Automobile auto)throws AutoException;
    int size();
    Automobile[] greater(int n);
    Automobile[] get_repo();

}
