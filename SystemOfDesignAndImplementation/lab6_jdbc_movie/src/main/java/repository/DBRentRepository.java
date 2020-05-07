package repository;

import domain.BaseEntity;
import domain.Client;
import domain.Movie;
import domain.Rent;
import domain.validators.ValidatorException;
import org.xml.sax.SAXException;

import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.TransformerException;
import java.io.IOException;
import java.sql.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

public class DBRentRepository<ID,T extends BaseEntity<ID>>implements Repository {
    private final String URL = "jdbc:postgresql://localhost:5432/MovieRental";
    private final String USER = System.getProperty("username");
    private final String Password = System.getProperty("password");

    @Override
    public Optional findOne(Object o) {
        return Optional.empty();
    }

    public DBRentRepository() {
    }

    @Override
    public Iterable findAll() throws SQLException {
        List<Rent> result = new ArrayList<>();
        String sql = "select * from Rent";


        Connection connection = DriverManager.getConnection(URL,USER,Password);
        PreparedStatement preparedStatement = connection.prepareStatement(sql);

        ResultSet resultSet = preparedStatement.executeQuery();
        while(resultSet.next()){
            Long id = resultSet.getLong("Id");
            Long rentedToClientId = resultSet.getLong("RentedToClientId");
            Long movieRentedId = resultSet.getLong("MovieRentedId");

            Rent rent = new Rent(id, rentedToClientId, movieRentedId, "startDate");
            result.add(rent);
        }
        return result;
    }

    @Override
    public Optional save(BaseEntity entity) throws ValidatorException, ParserConfigurationException, TransformerException, SAXException, IOException, SQLException {
        String sql = "insert into Rent (Id,RentedToClientId,MovieRentedId) values (?,?,?)";
        Connection connection = DriverManager.getConnection(URL,USER,Password);
        PreparedStatement preparedStatement = connection.prepareStatement(sql);
        preparedStatement.setLong(1,((Rent)entity).getId());
        preparedStatement.setLong(2,((Rent)entity).getRentedToClientId());
        preparedStatement.setLong(3,((Rent)entity).getMovieRentedId());
        int i = preparedStatement.executeUpdate();
        if(i==1)
            return Optional.ofNullable(entity);
        else
            return Optional.empty();
    }

    @Override
    public Optional delete(Object o) throws SQLException {
        String sql = "delete from Rent where Id=?";

        Connection connection = DriverManager.getConnection(URL,USER,Password);
        PreparedStatement preparedStatement = connection.prepareStatement(sql);

        preparedStatement.setLong(1,((Rent)o).getId());
        int i=preparedStatement.executeUpdate();

        if(i==1)
            return Optional.ofNullable(o);
        else
            return Optional.empty();
    }

    @Override
    public Optional update(BaseEntity entity) throws ValidatorException, SQLException {
        String sql = "update Rent set rentedToClientId=?, movieRentedId=? where Id=?";

        Connection connection = DriverManager.getConnection(URL,USER,Password);
        PreparedStatement preparedStatement = connection.prepareStatement(sql);

        preparedStatement.setLong(3,((Rent)entity).getId());
        preparedStatement.setLong(1,((Rent)entity).getRentedToClientId());
        preparedStatement.setLong(2,((Rent)entity).getMovieRentedId());
        int i=preparedStatement.executeUpdate();

        if(i==1)
            return Optional.ofNullable(entity);
        else
            return Optional.empty();
    }

    @Override
    public void saveToXml() throws ParserConfigurationException, IOException, SAXException, TransformerException {
        //pass
    }

    @Override
    public void loadFromXml() throws ParserConfigurationException, IOException, SAXException {
        //pass
    }
}
