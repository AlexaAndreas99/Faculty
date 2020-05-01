package Model;

public class Bike extends  Automobile {

    @Override
    public String get_name() {
        return super.get_name();
    }

    public Bike(int p, String n)
    {
        super(p,n);
    }

    @Override
    public String toString() {
        return super.toString();
    }

    @Override
    public int get_price() {
        return super.get_price();
    }
}
