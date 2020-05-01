package Repository;
import Model.*;
import Exception.*;
public class Repo implements Container{
    private Automobile[] a;
    private int ms;
    private int sz=0;

    public Repo(int i){
        this.a=new Automobile[i];
        this.ms=i;
    }
    @Override
    public Automobile[] get_repo(){
        Automobile[] aux=new Automobile[this.sz];
        System.arraycopy(this.a, 0, aux, 0, this.sz);
        return aux;
    }
    @Override
    public void add(Automobile auto)throws AutoException{
        if(this.ms<=this.sz)
            throw new AutoException("Max size has been reached");
        this.a[this.sz]=auto;
        this.sz++;
    }

    @Override
    public void remove(Automobile auto)throws AutoException {
        int i=this.find(auto);
        if(i==-1)
            throw new AutoException("The element does not exist!");
        if (this.sz - 1 - i >= 0) System.arraycopy(this.a, i + 1, this.a, i, this.sz - 1 - i);
        this.sz--;

    }
    @Override
    public int size(){
        return this.sz;

    }

    private int find(Automobile a){
        for(int i=0;i<this.sz;i++)
            if(this.a[i].get_name().equals(a.get_name()))
                return i;
        return -1;
    }

    @Override
    public Automobile[] greater(int n) {
         int j=0;

        for(int i=0;i<this.sz;i++)
            if(this.a[i].get_price()>=n)
                j++;

        Automobile[] aux=new Automobile[j];
        j=0;
        for(int i=0;i<this.sz;i++)
            if(this.a[i].get_price()>=n)
            {
                aux[j]=this.a[i];
                j++;
            }
         return aux;
    }


}
