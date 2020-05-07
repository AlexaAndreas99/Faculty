package repository;

import domain.Rent;
import domain.validators.Validator;
import domain.validators.ValidatorException;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.xml.sax.SAXException;

import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerException;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;
import java.util.*;
import java.util.stream.Collectors;
import java.util.stream.IntStream;
import java.util.stream.StreamSupport;

public class RentFileRepository extends InMemoryRepository<Long, Rent> {
    private String filename;

    public RentFileRepository(Validator<Rent> validator, String filename) {
        super(validator);
        this.filename = filename;
        //this.loadData();
    }

    private void loadData() {
        Path path = Paths.get(filename);

        try {
            Files.lines(path).forEach(line -> {
                List<String> items = Arrays.asList(line.split(","));

                Long rentId = Long.valueOf(items.get(0));
                Long rentedTo = Long.valueOf(items.get(1));
                Long MovieId = Long.valueOf(items.get(2));
                String dueDate = items.get(3);

                Rent rent = new Rent(rentId,rentedTo, MovieId, dueDate);
                //rent.setId(rentId);
                try {
                    super.save(rent);
                } catch (ValidatorException | ParserConfigurationException | TransformerException | SAXException | IOException e) {
                    e.printStackTrace();
                }
            });
        } catch (IOException ex) {
            ex.printStackTrace();
        }
    }

    public Optional<Rent> save(Rent entity) throws ValidatorException, ParserConfigurationException, IOException, SAXException, TransformerException {
        Optional<Rent> optional = super.save(entity);

        if (optional.isPresent()) {
            return optional;
        }
        saveToFile(entity);
        saveToXml();
        return Optional.empty();
    }

    private void saveToFile(Rent entity) {
        Path path = Paths.get(filename);

        try (BufferedWriter bufferedWriter = Files.newBufferedWriter(path, StandardOpenOption.APPEND)) {
            bufferedWriter.write(
                    entity.getId() + "," + entity.getRentedToClientId() + "," + entity.getMovieRentedId() + "," + entity.getStartDate());
            bufferedWriter.newLine();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @Override
    public void saveToXml() throws ParserConfigurationException, IOException, SAXException, TransformerException {
        FileWriter fileWriter = new FileWriter("rents.xml", false);
        String beggining = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><root></root>";
        fileWriter.write(beggining);
        fileWriter.close();

        Document document = DocumentBuilderFactory
                .newInstance()
                .newDocumentBuilder()
                .parse("rents.xml");

        Iterable<Rent> rentIterable = findAll();
        Set s = StreamSupport.stream(rentIterable.spliterator(), false).map(rent -> rentToNode(rent, document)).collect(Collectors.toSet());
        Element root = document.getDocumentElement();
        s.stream().forEach(node -> {root.appendChild((Node) node);});
        Transformer transformer = TransformerFactory.newInstance().newTransformer();
        transformer.transform(new DOMSource(document), new StreamResult(new File("./data/rents.xml")));
    }

    private Node rentToNode(Rent rent, Document document) {
        Element rentElement = document.createElement("rent");
        rentElement.setAttribute("id", rent.getId().toString());

        Element rentedToClientId = document.createElement("rentedToClientId");
        rentedToClientId.setTextContent(Long.toString(rent.getRentedToClientId()));

        Element movieRentedId = document.createElement("movieRentedId");
        movieRentedId.setTextContent(Long.toString(rent.getRentedToClientId()));

        Element dueDate = document.createElement("dueDate");
        dueDate.setTextContent(rent.getStartDate());

        rentElement.appendChild(rentedToClientId);
        rentElement.appendChild(movieRentedId);
        rentElement.appendChild(dueDate);

        return rentElement;
    }

    public void loadFromXml() throws ParserConfigurationException, IOException, SAXException {
        List<Rent> result = new ArrayList<>();

        Document document = DocumentBuilderFactory
                .newInstance()
                .newDocumentBuilder()
                .parse("./data/rents.xml");

        Element root = document.getDocumentElement();

        NodeList children = root.getChildNodes();
        result = IntStream
                .range(0, children.getLength())
                .mapToObj(index -> children.item(index))
                .filter(node -> node instanceof Element)
                .map(node -> createRentFromElement((Element) node))
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

    private Rent createRentFromElement (Element rentElement) {
        Rent rent = new Rent();

        Long id = Long.valueOf(rentElement.getAttribute("id"));
        rent.setId(id);

        Node rentedToClientIdNode = rentElement.getElementsByTagName("rentedToClientId").item(0);
        Long rentedToClientId = Long.valueOf(rentedToClientIdNode.getTextContent());
        rent.setRentedToClientId(rentedToClientId);

        Node movieRentedIdNode = rentElement.getElementsByTagName("movieRentedId").item(0);
        Long movieRentedId = Long.valueOf(movieRentedIdNode.getTextContent());
        rent.setRentedToClientId(movieRentedId);

        Node dueDateNode = rentElement.getElementsByTagName("dueDate").item(0);
        String dueDate = dueDateNode.getTextContent();
        rent.setStartDate(dueDate);

        return rent;
    }

}
