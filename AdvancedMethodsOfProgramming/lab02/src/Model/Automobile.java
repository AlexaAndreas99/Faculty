package Model;

public abstract class Automobile{
    private int price;
    private String name;

    Automobile(int p, String n) {
        this.price = p;
        this.name=n;
    }
    public int get_price(){
        return this.price;
    }
    public String get_name(){
        return this.name;
    }
    public String toString() {
        return this.price +" "+this.name;
    }
}
