package Controller;
import Model.Automobile;
import Repository.*;
import Exception.AutoException;
public class Ctrl {
    private Container c;
    public Ctrl(Container c)
    {
        this.c=c;
    }
    public void  add(Automobile a)throws AutoException {
            this.c.add(a);

    }
    public void remove(Automobile a)throws AutoException{
        this.c.remove(a);
    }
    public Automobile[] get_greater(int n){
        return this.c.greater(n);
    }
    public Automobile[] get_all(){
        return this.c.get_repo();
    }
}
