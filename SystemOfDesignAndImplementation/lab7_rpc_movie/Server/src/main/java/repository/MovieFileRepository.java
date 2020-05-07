package repository;

import domain.Client;
import domain.Movie;
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

public class MovieFileRepository extends InMemoryRepository<Long, Movie> {

    private String filename;

    public MovieFileRepository(Validator<Movie> validator, String filename) {
        super(validator);
        this.filename = filename;
        //this.loadData();
    }

    @Override
    public Optional<Movie> save(Movie entity) throws ValidatorException, ParserConfigurationException, TransformerException, SAXException, IOException {
        Optional<Movie> optional = super.save(entity);
        if (optional.isPresent()) {
            return optional;
        }
        saveToFile(entity);
        saveToXml();
        return Optional.empty();
    }

    private void saveToFile(Movie entity) {
        Path path = Paths.get(this.filename);

        try (BufferedWriter bufferedWriter = Files.newBufferedWriter(path, StandardOpenOption.APPEND)) {
            bufferedWriter.write(
                    entity.getId() + "," + entity.getName() + "," + entity.getTimesRented());
            bufferedWriter.newLine();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void loadData() {
        Path path = Paths.get(filename);

        try {
            Files.lines(path).forEach(line -> {
                List<String> items = Arrays.asList(line.split(","));

                Long id = Long.valueOf(items.get(0));
                String name = items.get(1);
                int tr = Integer.parseInt(items.get(2));

                Movie movie = new Movie(id, name, tr);
                try {
                    super.save(movie);
                } catch (ValidatorException | ParserConfigurationException | TransformerException | SAXException | IOException e) {
                    e.printStackTrace();
                }
            });
        } catch (IOException ex) {
            ex.printStackTrace();
        }
    }
    @Override
    public void saveToXml() throws ParserConfigurationException, IOException, SAXException, TransformerException {
        FileWriter fileWriter = new FileWriter("movies.xml", false);
        String beggining = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><root></root>";
        fileWriter.write(beggining);
        fileWriter.close();

        Document document = DocumentBuilderFactory
                .newInstance()
                .newDocumentBuilder()
                .parse("movies.xml");

        Iterable<Movie> movieIterable = findAll();
        Set s = StreamSupport.stream(movieIterable.spliterator(), false).map(movie -> movieToNode(movie, document)).collect(Collectors.toSet());
        Element root = document.getDocumentElement();
        s.stream().forEach(node -> {root.appendChild((Node) node);});
        Transformer transformer = TransformerFactory.newInstance().newTransformer();
        transformer.transform(new DOMSource(document), new StreamResult(new File("./data/movies.xml")));
    }

    private Node movieToNode(Movie movie, Document document) {
        Element movieElement = document.createElement("movie");
        movieElement.setAttribute("id", movie.getId().toString());

        Element nameElement = document.createElement("name");
        nameElement.setTextContent(movie.getName());

        Element timesRented = document.createElement("timesRented");
        timesRented.setTextContent(Integer.toString(movie.getTimesRented()));

        movieElement.appendChild(nameElement);
        movieElement.appendChild(timesRented);

        return movieElement;
    }

    public void loadFromXml() throws ParserConfigurationException, IOException, SAXException {
        List<Movie> result = new ArrayList<>();

        Document document = DocumentBuilderFactory
                .newInstance()
                .newDocumentBuilder()
                .parse("./data/movies.xml");

        Element root = document.getDocumentElement();

        NodeList children = root.getChildNodes();
        result = IntStream
                .range(0, children.getLength())
                .mapToObj(index -> children.item(index))
                .filter(node -> node instanceof Element)
                .map(node -> createMovieFromElement((Element) node))
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

    private Movie createMovieFromElement (Element movieElement) {
        Movie movie = new Movie();

        Long id = Long.valueOf(movieElement.getAttribute("id"));
        movie.setId(id);

        Node nameNode = movieElement.getElementsByTagName("name").item(0);
        String name = nameNode.getTextContent();
        movie.setName(name);

        Node timesRentedNode = movieElement.getElementsByTagName("timesRented").item(0);
        int timesRented = Integer.parseInt(timesRentedNode.getTextContent());
        movie.setTimesRented(timesRented);

        return movie;
    }
    public List<Movie> getMoviesByName(String name){
        return super.entities.values().stream().filter(movie -> movie.getName().contains(name)).collect(Collectors.toList());
    }
    public Movie getMostRentedMovie(){
        int n = super.entities.values().stream().map(Movie::getTimesRented).max(Comparator.comparing(Integer::valueOf)).get();
        return super.entities.values().stream().filter(m -> m.getTimesRented()==n).limit(1).findFirst().get();
    }
}
