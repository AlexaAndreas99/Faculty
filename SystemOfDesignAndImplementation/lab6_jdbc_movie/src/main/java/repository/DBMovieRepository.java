package repository;

import domain.BaseEntity;
import domain.Movie;
import domain.validators.ValidatorException;
import org.xml.sax.SAXException;

import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.TransformerException;
import java.io.IOException;
import java.sql.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

public class DBMovieRepository<ID,T extends BaseEntity<ID>>implements Repository {
    private final String URL = "jdbc:postgresql://localhost:5432/MovieRental";
    private final String USER = System.getProperty("username");
    private final String Password = System.getProperty("password");

    @Override
    public Optional findOne(Object o) {
        return Optional.empty();
    }

    public DBMovieRepository() {
    }

    @Override
    public Iterable findAll() throws SQLException {
        List<Movie> result = new ArrayList<>();
        String sql = "select * from Movie";


        Connection connection = DriverManager.getConnection(URL,USER,Password);
        PreparedStatement preparedStatement = connection.prepareStatement(sql);

        ResultSet resultSet = preparedStatement.executeQuery();
        while(resultSet.next()){
            Long id = resultSet.getLong("Id");
            String name = resultSet.getString("Name");
            int timesRented = resultSet.getInt("TimesRented");

            Movie movie = new Movie(id, name,timesRented);
            result.add(movie);
        }
        return result;
    }

    @Override
    public Optional save(BaseEntity entity) throws ValidatorException, ParserConfigurationException, TransformerException, SAXException, IOException, SQLException {
        String sql = "insert into Movie (Id,Name,TimesRented) values (?,?,?)";
        Connection connection = DriverManager.getConnection(URL,USER,Password);
        PreparedStatement preparedStatement = connection.prepareStatement(sql);
        preparedStatement.setLong(1, ((Movie)entity).getId());
        preparedStatement.setString(2,((Movie)entity).getName());
        preparedStatement.setInt(3,((Movie)entity).getTimesRented());
        int i = preparedStatement.executeUpdate();
        if(i==1)
            return Optional.ofNullable(entity);
        else
            return Optional.empty();
    }

    @Override
    public Optional delete(Object o) throws SQLException {
        String sql = "delete from Movie where Id=?";

        Connection connection = DriverManager.getConnection(URL,USER,Password);
        PreparedStatement preparedStatement = connection.prepareStatement(sql);

        preparedStatement.setLong(1,((Movie)o).getId());
        int i=preparedStatement.executeUpdate();

        if(i==1)
            return Optional.ofNullable(o);
        else
            return Optional.empty();
    }

    @Override
    public Optional update(BaseEntity entity) throws ValidatorException, SQLException {
        String sql = "update Movie set Name=?, TimesRented=? where Id=?";

        Connection connection = DriverManager.getConnection(URL,USER,Password);
        PreparedStatement preparedStatement = connection.prepareStatement(sql);

        preparedStatement.setLong(3,((Movie)entity).getId());
        preparedStatement.setString(1,((Movie)entity).getName());
        preparedStatement.setInt(2,((Movie)entity).getTimesRented());
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
