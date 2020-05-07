package domain;

public class Rent extends BaseEntity<Long> {
    private long rentedToClientId;
    private long movieRentedId;
    private String startDate;

    @Override
    public String toString() {
        return "ID: " + super.getId()+
                " rentedToClientId: " + rentedToClientId +
                " movieRentedId: " + movieRentedId +
                " dueDate: '" + startDate + '\'';
    }

    public long getRentedToClientId() {
        return rentedToClientId;
    }

    public void setRentedToClientId(long rentedToClientId) {
        this.rentedToClientId = rentedToClientId;
    }

    public long getMovieRentedId() {
        return movieRentedId;
    }

    public void setMovieRentedId(long movieRentedId) {
        this.movieRentedId = movieRentedId;
    }

    public String getStartDate() {
        return startDate;
    }

    public void setStartDate(String startDate) {
        this.startDate = startDate;
    }

    public Rent(long id, long rentedToClientId, long movieRentedId, String startDate) {
        super.setId(id);
        this.rentedToClientId = rentedToClientId;
        this.movieRentedId = movieRentedId;
        this.startDate = startDate;
    }
    public Rent(){}
}
