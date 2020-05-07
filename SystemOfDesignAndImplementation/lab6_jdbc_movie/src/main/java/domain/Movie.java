package domain;

public class Movie extends  BaseEntity<Long> {
    private String name;
    private int timesRented;


    @Override
    public String toString() {
        return "ID: "+super.getId()+", Name: "+name+", Times rented: "+timesRented;
    }
    public void incTimesRented(){this.timesRented++;}

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getTimesRented() {
        return timesRented;
    }

    public void setTimesRented(int timesRented) {
        this.timesRented = timesRented;
    }

    public Movie(Long id, String name,int timesRented) {
        super.setId(id);
        this.name = name;
        this.timesRented = timesRented;
    }
    public Movie(){}

}
