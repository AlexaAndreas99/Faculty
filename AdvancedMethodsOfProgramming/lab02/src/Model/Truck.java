package Model;

public class Truck extends Automobile{

    @Override
    public String get_name() {
        return super.get_name();
    }

    public Truck(int p, String n){
        super(p,n);
    }

    @Override
    public int get_price() {
        return super.get_price();
    }

    @Override
    public String toString() {
        return super.toString();
    }
}
