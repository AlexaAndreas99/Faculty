package repository;

import domain.BaseEntity;
import domain.Client;
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

public class DBClientRepository<ID,T extends BaseEntity<ID>>implements Repository {
    private final String URL = "jdbc:postgresql://localhost:5432/MovieRental";
    private final String USER = System.getProperty("username");
    private final String Password = System.getProperty("password");

    @Override
    public Optional findOne(Object o) {
        return Optional.empty();
    }

    public DBClientRepository() {
    }

    @Override
    public Iterable findAll() throws SQLException {
        List<Client> result = new ArrayList<>();
        String sql = "select * from Client";


        Connection connection = DriverManager.getConnection(URL,USER,Password);
        PreparedStatement preparedStatement = connection.prepareStatement(sql);

        ResultSet resultSet = preparedStatement.executeQuery();
        while(resultSet.next()){
            Long id = resultSet.getLong("Id");
            String name = resultSet.getString("Name");
            String cnp = resultSet.getString("Cnp");

            Client client = new Client(id, cnp, name);
            result.add(client);
        }
        return result;
    }

    @Override
    public Optional save(BaseEntity entity) throws ValidatorException, ParserConfigurationException, TransformerException, SAXException, IOException, SQLException {
        String sql = "insert into Client (Id,Name,Cnp) values (?,?,?)";
        Connection connection = DriverManager.getConnection(URL,USER,Password);
        PreparedStatement preparedStatement = connection.prepareStatement(sql);
        preparedStatement.setLong(1, ((Client)entity).getId());
        preparedStatement.setString(2,((Client)entity).getName());
        preparedStatement.setString(3,((Client)entity).getCnp());
        int i = preparedStatement.executeUpdate();
        if(i==1)
            return Optional.ofNullable(entity);
        else
            return Optional.empty();
    }

    @Override
    public Optional delete(Object o) throws SQLException {
        String sql = "delete from Client where Id=?";

        Connection connection = DriverManager.getConnection(URL,USER,Password);
        PreparedStatement preparedStatement = connection.prepareStatement(sql);

        preparedStatement.setLong(1,((Client)o).getId());
        int i=preparedStatement.executeUpdate();

        if(i==1)
            return Optional.ofNullable(o);
        else
            return Optional.empty();
    }

    @Override
    public Optional update(BaseEntity entity) throws ValidatorException, SQLException {
        String sql = "update Client set Name=?, Cnp=? where Id=?";

        Connection connection = DriverManager.getConnection(URL,USER,Password);
        PreparedStatement preparedStatement = connection.prepareStatement(sql);

        preparedStatement.setLong(3,((Client)entity).getId());
        preparedStatement.setString(1,((Client)entity).getName());
        preparedStatement.setString(2,((Client)entity).getCnp());
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
