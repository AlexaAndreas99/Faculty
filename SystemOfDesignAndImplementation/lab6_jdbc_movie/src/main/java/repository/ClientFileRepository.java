package repository;

import domain.Client;
import domain.Movie;
import domain.validators.Validator;
import domain.validators.ValidatorException;

import java.io.*;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;
import java.util.*;

import org.w3c.dom.*;
import org.xml.sax.EntityResolver;
import org.xml.sax.ErrorHandler;
import org.xml.sax.InputSource;
import org.xml.sax.SAXException;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerConfigurationException;
import javax.xml.transform.TransformerException;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;
import java.io.IOException;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.IntStream;
import java.util.stream.StreamSupport;

//@Sergiu
public class ClientFileRepository  extends InMemoryRepository<Long, Client> {
    final int CLIENT_INDEX_ID = 0;
    final int CLIENT_INDEX_NAME = 1;
    final int CLIENT_INDEX_CNP = 2;

    private String filename;

    public ClientFileRepository(Validator<Client> validator, String filename) {
        super(validator);
        this.filename = filename;
        //this.loadData();
    }

    private void loadData() {
        Path path = Paths.get(filename);

        try {
            Files.lines(path).forEach(line -> {
                List<String> items = Arrays.asList(line.split(","));

                Long id = Long.valueOf(items.get(CLIENT_INDEX_ID));
                String name = items.get(CLIENT_INDEX_NAME);
                String cnp = items.get(CLIENT_INDEX_CNP);

                Client client = new Client(id, cnp,name);
                try {
                    super.save(client);
                } catch (ValidatorException | ParserConfigurationException | TransformerException | SAXException | IOException e) {
                    e.printStackTrace();
                }
            });
        } catch (IOException ex) {
            ex.printStackTrace();
        }
    }

    public Optional<Client> save(Client entity) throws ValidatorException, ParserConfigurationException, IOException, SAXException, TransformerException {
        Optional<Client> optional = super.save(entity);

        if (optional.isPresent()) {
            return optional;
        }
        saveToFile(entity);
        saveToXml();
        return Optional.empty();
    }

    private void saveToFile(Client entity) {
        Path path = Paths.get(filename);

        try (BufferedWriter bufferedWriter = Files.newBufferedWriter(path, StandardOpenOption.APPEND)) {
            bufferedWriter.write(
                    entity.getId() + "," + entity.getName() + "," + entity.getName());
            bufferedWriter.newLine();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    @Override
    public void saveToXml() throws ParserConfigurationException, IOException, SAXException, TransformerException {
        FileWriter fileWriter = new FileWriter("clients.xml", false);
        String beggining = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><root></root>";
        fileWriter.write(beggining);
        fileWriter.close();

        Document document = DocumentBuilderFactory
                .newInstance()
                .newDocumentBuilder()
                .parse("clients.xml");

        Iterable<Client> clientIterable = findAll();
        Set s = StreamSupport.stream(clientIterable.spliterator(), false).map(client -> clientToNode(client, document)).collect(Collectors.toSet());
        Element root = document.getDocumentElement();
        s.stream().forEach(node -> {root.appendChild((Node) node);});
        Transformer transformer = TransformerFactory.newInstance().newTransformer();
        transformer.transform(new DOMSource(document), new StreamResult(new File("./data/clients.xml")));
    }

    private Node clientToNode(Client client, Document document) {
        Element clientElement = document.createElement("client");
        clientElement.setAttribute("id", client.getId().toString());

        Element cnpElement = document.createElement("cnp");
        cnpElement.setTextContent(client.getCnp());

        Element nameElement = document.createElement("name");
        nameElement.setTextContent(client.getName());

        clientElement.appendChild(cnpElement);
        clientElement.appendChild(nameElement);

        return clientElement;
    }

    public void loadFromXml() throws ParserConfigurationException, IOException, SAXException {
        List<Client> result = new ArrayList<>();

        Document document = DocumentBuilderFactory
                .newInstance()
                .newDocumentBuilder()
                .parse("./data/clients.xml");

        Element root = document.getDocumentElement();

        NodeList children = root.getChildNodes();
        result = IntStream
                .range(0, children.getLength())
                .mapToObj(index -> children.item(index))
                .filter(node -> node instanceof Element)
                .map(node -> createClientFromElement((Element) node))
                .collect(Collectors.toList());
        result.stream().forEach(entity -> {
            try {
                super.save(entity);
            } catch (ParserConfigurationException e) {
                e.printStackTrace();
            } catch (TransformerException e) {
                e.printStackTrace();
            } catch (SAXException e) {
                e.printStackTrace();
            } catch (IOException e) {
                e.printStackTrace();
            }
        });
    }

    private Client createClientFromElement(Element clientElement) {
        Client client = new Client();

        Long id = Long.valueOf(clientElement.getAttribute("id"));
        client.setId(id);

        Node cnpNode = clientElement.getElementsByTagName("cnp").item(0);
        String cnp = cnpNode.getTextContent();
        client.setCnp(cnp);

        Node nameNode = clientElement.getElementsByTagName("name").item(0);
        String name = nameNode.getTextContent();
        client.setName(name);

        return client;
    }
}
