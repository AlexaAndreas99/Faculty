package ui;

import org.xml.sax.SAXException;

import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.TransformerException;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.nio.channels.ClosedByInterruptException;
import java.sql.SQLException;
import java.util.List;
import java.util.NoSuchElementException;
import java.util.Set;

public class Console {

    //url-"jdbc:postgresql://localhost:5432/MovieRental"


//    public void runConsole() {
//        try {
//            //rentService.loadFromXml();
//            //this.printAllRents();
//            movieService.loadFromXml();
//            this.printAllMovies();
//            this.movieService.getMoviesByName("Avengers").forEach(System.out::println);
//            System.out.println(this.movieService.getMostRentedMovie());
//        }
//        catch (Exception e) {
//            e.printStackTrace();
//        }
//
//        //this.printAllMovies();
//        //this.printAllClients();
//        //this.printAllRents();
//        //this.deleteClient();
//        //this.deleteMovie();
//        //addMovie();
//        //this.updateClient();
//        //this.printAllClients();
//        //this.updateMovie();
//        //this.printAllMovies();
//    }
//
//    private void printAllMovies() throws SQLException {
//        Set<Movie> movies = movieService.getAllMovies();
//        movies.stream().forEach(System.out::println);
//    }
//
//    private void printAllClients() throws SQLException {
//        Set<Client> clients = clientService.getAllClients();
//        clients.stream().forEach(System.out::println);
//    }
//
//    private void printAllRents() throws SQLException {
//        Set<Rent> rents = rentService.getAllRents();
//        rents.stream().forEach(System.out::println);
//    }
//
//    private void addMovie() {
//        while (true) {
//            Movie movie = readMovie();
//            if (movie.getId() < 0) {
//                break;
//            }
//            try {
//                movieService.addMovie(movie);
//            } catch (ValidatorException | ParserConfigurationException | IOException | SAXException | TransformerException | SQLException e) {
//                e.printStackTrace();
//            }
//        }
//    }
//
//    private Movie readMovie() {
//        System.out.println("Read movie {id,Movie name}");
//
//        BufferedReader bufferRead = new BufferedReader(new InputStreamReader(System.in));
//        try {
//            Long id = Long.valueOf(bufferRead.readLine());// ...
//            String name = bufferRead.readLine();
//
//            Movie movie = new Movie(id, name, 0);
//
//            return movie;
//        } catch (IOException ex) {
//            ex.printStackTrace();
//        }
//        return null;
//    }
//
//    private void updateMovie() {
//        System.out.println("Enter client ID: ");
//        BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(System.in));
//
//        try {
//            long id = Long.parseLong(bufferedReader.readLine());
//            Movie movie = movieService.getMovieById(id);
//            String name = movie.getName();
//            int timesRented = movie.getTimesRented();
//
//            System.out.println("1. Update Name\n2. Update Times Rented\n3. Update Rented to");
//            int input = Integer.parseInt(bufferedReader.readLine());
//
//            switch (input) {
//                case 1:
//                    name = bufferedReader.readLine();
//                    break;
//                case 2:
//                    //rentedTo = Integer.parseInt(bufferedReader.readLine());
//                    break;
//                case 3:
//                    timesRented = Integer.parseInt(bufferedReader.readLine());
//                    break;
//                default:
//                    throw new IOException("Invalid choice");
//            }
//            Movie newMovie = new Movie(id, name, timesRented);
//            movieService.updateMovie(newMovie);
//        } catch (IOException | ValidatorException | NoSuchElementException | SQLException e) {
//            e.printStackTrace();
//        }
//    }
//
//    private void updateClient() {
//        System.out.println("Enter client ID: ");
//        BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(System.in));
//
//        try {
//            long id = -1;
//            id = Long.parseLong(bufferedReader.readLine());
//            Client client = clientService.getClientById(id);
//            String name = client.getName();
//            String cnp = client.getCnp();
//
//            System.out.println("1. Update Name\n2. Update CNP");
//            int input = Integer.parseInt(bufferedReader.readLine());
//
//            switch (input) {
//                case 1:
//                    name = bufferedReader.readLine();
//                    break;
//                case 2:
//                    cnp = bufferedReader.readLine();
//                    break;
//                default:
//                    throw new IOException("Invalid choice");
//            }
//            Client updatedClient = new Client(id, cnp, name);
//            clientService.updateClient(updatedClient);
//        } catch (IOException | ValidatorException | NoSuchElementException | SQLException e) {
//            e.printStackTrace();
//        }
//    }
//
//    private void deleteClient() {
//        System.out.println("Enter Client ID: ");
//        BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(System.in));
//
//        try {
//            long id = Long.parseLong(bufferedReader.readLine());
//            clientService.getClientById(id);
//
//            clientService.deleteClient(id);
//
//        } catch (IOException | NoSuchElementException | SQLException e) {
//            e.printStackTrace();
//        }
//    }
//
//    private void deleteMovie() {
//        System.out.println("Enter Movie ID: ");
//        BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(System.in));
//
//        try {
//            long id = Long.parseLong(bufferedReader.readLine());
//            movieService.getMovieById(id);
//            movieService.deleteMovie(id);
//
//        } catch (IOException | NoSuchElementException | SQLException e) {
//            e.printStackTrace();
//        }
//    }
}
