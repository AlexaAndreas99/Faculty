package service;

import domain.Rent;
import org.xml.sax.SAXException;
import repository.Repository;

import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.TransformerException;
import java.io.IOException;
import java.sql.SQLException;
import java.util.NoSuchElementException;
import java.util.Set;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

public class RentService {
    private Repository<Long, Rent> rentRepository;

    public RentService(Repository<Long, Rent> rentRepository) {
        this.rentRepository = rentRepository;
    }

    public void addRent(Rent newRent) throws ParserConfigurationException, IOException, SAXException, TransformerException, SQLException { rentRepository.save(newRent);}
    public Set<Rent> getAllRents() throws SQLException {
        Iterable<Rent> rents = rentRepository.findAll();
        return StreamSupport.stream(rents.spliterator(),false).collect(Collectors.toSet());
    }

    public Rent getRentById(long id)throws NoSuchElementException{
        return rentRepository.findOne(id).get();
    }
    public void deleteClient(long id) throws SQLException {
        rentRepository.delete(id);
    }

    public void saveToXml() throws ParserConfigurationException, TransformerException, SAXException, IOException {
        rentRepository.saveToXml();
    }

    public void loadFromXml() throws IOException, SAXException, ParserConfigurationException {
        rentRepository.loadFromXml();
    }
}
