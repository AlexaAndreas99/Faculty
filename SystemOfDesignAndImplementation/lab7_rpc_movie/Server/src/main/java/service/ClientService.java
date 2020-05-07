package service;
//@Sergiu

import domain.Client;
import domain.validators.ValidatorException;
import org.xml.sax.SAXException;
import repository.Repository;

import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.TransformerException;
import java.io.IOException;
import java.sql.SQLException;
import java.util.List;
import java.util.NoSuchElementException;
import java.util.Set;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

public class ClientService {
    private Repository<Long, Client> clientRepository;

    public ClientService(Repository<Long, Client> repository) {
        this.clientRepository = repository;
    }

    public void addClient(Client newClient) throws ParserConfigurationException, IOException, SAXException, TransformerException, SQLException {
        clientRepository.save(newClient);
    }

    public Set<Client> getAllClients() throws SQLException {
        Iterable<Client> clients = clientRepository.findAll();
        return StreamSupport.stream(clients.spliterator(), false).collect(Collectors.toSet());
    }

    public Client getClientById(long id) throws NoSuchElementException {
        return clientRepository.findOne(id).get();
    }

    public void updateClient(Client updatedClient) throws ValidatorException, SQLException {
        clientRepository.update(updatedClient);
    }

    public void deleteClient(long id ) throws SQLException {
        clientRepository.delete(id);
    }

    public void saveToXml() throws ParserConfigurationException, TransformerException, SAXException, IOException {
        clientRepository.saveToXml();
    }

    public void loadFromXml() {
        try{
            clientRepository.loadFromXml();
        }
        catch (Exception e){
            e.printStackTrace();
        }
    }
}
