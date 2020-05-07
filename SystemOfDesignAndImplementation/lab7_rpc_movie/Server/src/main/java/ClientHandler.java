import domain.Client;
import domain.Movie;
import domain.Rent;
import domain.validators.ClientValidator;
import domain.validators.MovieValidator;
import domain.validators.RentValidator;
import domain.validators.Validator;
import org.xml.sax.SAXException;
import repository.ClientFileRepository;
import repository.MovieFileRepository;
import repository.RentFileRepository;
import repository.Repository;
import service.ClientService;
import service.MovieService;
import service.RentService;

import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.TransformerException;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.sql.SQLException;
import java.util.Set;

public class ClientHandler implements Runnable {
    InputStream in;
    OutputStream out;
    MovieService movieService;
    ClientService clientService;
    RentService rentService;

    ClientHandler(InputStream in, OutputStream out) {
        this.in = in;
        this.out = out;
        Validator<Movie> movieValidator = new MovieValidator();
        Validator<Client> clientValidator = new ClientValidator();
        Validator<Rent> rentValidator = new RentValidator();

        Repository<Long, Movie> movieRepository = new MovieFileRepository(movieValidator, "./data/movies");
        Repository<Long, Client> clientRepository = new ClientFileRepository(clientValidator, "./data/clients");
        Repository<Long, Rent> rentRepository = new RentFileRepository(rentValidator, "./data/rents");

        //Repository<Long,Movie> dbMovieRepository = new DBClientRepository<>();
        //MovieService movieService = new MovieService(dbMovieRepository);

        movieService = new MovieService(movieRepository);
        clientService = new ClientService(clientRepository);
        rentService = new RentService(rentRepository);

        movieService.loadFromXml();
        clientService.loadFromXml();
        //rentService.loadFromXml();
    }

    @Override
    public void run() {
        Message request = new Message();
        try {
            request.readFrom(in);
            String messageAsString = request.toString();
            System.out.println("received request: " + messageAsString);

            String header = request.getHeader();
            String body = request.getBody();

            if (header.contains("Add client")) {
                String[] params = body.split(" ");
                Long id = Long.valueOf(params[0]);
                String cnp = params[1];
                String name = params[2];
                clientService.addClient(new Client(id, cnp, name));

                Message m = new Message("add", "sucessfully");
                m.writeTo(out);
            }
            if (header.contains("Add movie")) {
                String[] params = body.split(" ");
                Long id = Long.valueOf(params[0]);
                String name = params[1];
                int tr = Integer.parseInt(params[2]);

                Movie movie = new Movie(id, name, tr);
                movieService.addMovie(movie);
                Message m = new Message("add", "sucessfully");
                m.writeTo(out);
            }
            if (header.contains("Add rent")) {
                String[] params = body.split(" ");
                Long rentId = Long.valueOf(params[0]);
                Long rentedTo = Long.valueOf(params[1]);
                Long MovieId = Long.valueOf(params[2]);
                String dueDate = params[3];
                rentService.addRent(new Rent(rentId, rentedTo, MovieId, dueDate));
                Message m = new Message("add", "sucessfully");
                m.writeTo(out);
            }

            if (header.contains("Delete client")) {
                String[] params = body.split(" ");
                Long id = Long.valueOf(params[0]);
                clientService.deleteClient(id);
                Message m = new Message("delete", "sucessfully");
                m.writeTo(out);
            }
            if (header.contains("Delete movie")) {
                String[] params = body.split(" ");
                Long id = Long.valueOf(params[0]);
                movieService.deleteMovie(id);
                Message m = new Message("delete", "sucessfully");
                m.writeTo(out);
            }
            if (header.contains("Delete rent")) {
                String[] params = body.split(" ");
                Long id = Long.valueOf(params[0]);
                rentService.deleteClient(id);
                Message m = new Message("delete", "sucessfully");
                m.writeTo(out);
            }

            if (header.contains("Update client")) {
                String[] params = body.split(" ");
                Long id = Long.valueOf(params[0]);
                String cnp = params[1];
                String name = params[2];
                clientService.updateClient(new Client(id, cnp, name));
                Message m = new Message("Update", "sucessfully");
                m.writeTo(out);
            }
            if (header.contains("Update movie")) {
                String[] params = body.split(" ");
                Long id = Long.valueOf(params[0]);
                String name = params[1];
                int tr = Integer.parseInt(params[2]);

                Movie movie = new Movie(id, name, tr);
                movieService.updateMovie(movie);
                Message m = new Message("Update", "sucessfully");
                m.writeTo(out);
            }
            if (header.contains("Update rent")) {
                String[] params = body.split(" ");
                Long rentId = Long.valueOf(params[0]);
                Long rentedTo = Long.valueOf(params[1]);
                Long MovieId = Long.valueOf(params[2]);
                String dueDate = params[3];
                rentService.addRent(new Rent(rentId, rentedTo, MovieId, dueDate));
                Message m = new Message("Update", "sucessfully");
                m.writeTo(out);
            }

            if (header.contains("Delete client")) {
                String[] params = body.split(" ");
                clientService.deleteClient(Long.valueOf(params[0]));
                Message m = new Message("delete", "sucessfully");
                m.writeTo(out);
            }
            if (header.contains("Delete movie")) {
                String[] params = body.split(" ");
                movieService.deleteMovie(Long.valueOf(params[0]));
                Message m = new Message("delete", "sucessfully");
                m.writeTo(out);
            }
            if (header.contains("Delete rent")) {
                String[] params = body.split(" ");
                Message m = new Message("delete", "sucessfully");
                m.writeTo(out);
            }
            if (header.contains("Print clients")) {
                Set<Client> s = clientService.getAllClients();
                String all = new String();

                all += s.toString();

                Message response = new Message("print", all);
                response.writeTo(out);
            }
            if (header.contains("Print movies")) {
                System.out.println("will print movies to client now...");
                Set<Movie> m = movieService.getAllMovies();
                String all = new String();

                all += m.toString();

                Message response = new Message("print", all);
                response.writeTo(out);
            }
            if (header.contains("Print rents")) {
                Set<Rent> r = rentService.getAllRents();
                String all = new String();

                all += r.toString();

                Message response = new Message("print", all);
                response.writeTo(out);
            }
        } catch (IOException e) {
            e.printStackTrace();
        } catch (SQLException e) {
            e.printStackTrace();
        } catch (ParserConfigurationException e) {
            e.printStackTrace();
        } catch (SAXException e) {
            e.printStackTrace();
        } catch (TransformerException e) {
            e.printStackTrace();
        }
    }

//    private void menu(String[] str) throws Exception {
//        if (str[0].contains("movies")) {
//            Set<Movie> movies = this.getAllMovies();
//            movies.stream().forEach(m -> out.println(m.toString()));
//            out.flush();
//        }
//        else if (str[0].contains("clients")) {
//            Set<Client> clients = this.getAllClients();
//            clients.stream().forEach(m -> out.println(m.toString()));
//            out.flush();
//        }
//        else if (str[0].contains("rents")) {
//            Set<Rent> rents = this.getAllRents();
//            rents.stream().forEach(m -> out.println(m.toString()));
//            out.flush();
//        }
//        else if (str[0].contains("add")) {
//            if (str[1].contains("movie")) {
//                Movie m = new Movie(Long.parseLong(str[2]), str[3], Integer.parseInt(str[4]));
//                movieService.addMovie(m);
//                out.println("Movie added successfully");
//                out.flush();
//            }
//            if (str[1].contains("client")) {
//                Client c = new Client(Long.parseLong(str[2]), str[3], str[4]);
//                clientService.addClient(c);
//                out.println("Client added successfully");
//                out.flush();
//            }
//            if (str[1].contains("rent")) {
//                Rent r = new Rent(Long.parseLong(str[2]), Long.parseLong(str[3]), Long.parseLong(str[4]), str[5]);
//                rentService.addRent(r);
//                out.println("Rent added successfully");
//                out.flush();
//            }
//        } else if (str[0].contains("delete")) {
//            if (str[1].contains("movie")) {
//                long id = Long.parseLong(str[2]);
//                movieService.getMovieById(id);
//                movieService.deleteMovie(id);
//                out.println("Movie deleted successfully");
//                out.flush();
//            }
//            if (str[1].contains("client")) {
//                long id = Long.parseLong(str[2]);
//                clientService.getClientById(id);
//                clientService.deleteClient(id);
//                out.println("Client deleted successfully");
//                out.flush();
//            }
//        } else if (str[0].contains("update")) {
//            if (str[1].contains("movie")) {
//                //TODO
//                out.println("Movie updated successfully");
//                out.flush();
//            }
//            if (str[1].contains("client")) {
//                long id = Long.parseLong(str[2]);
//                //TODO
//                out.println("Client updated successfully");
//                out.flush();
//            }
//        } else throw new Exception("Invalid request");
//    }

    private Set<Movie> getAllMovies() throws SQLException {
        return movieService.getAllMovies();
    }

    private Set<Client> getAllClients() throws SQLException {
        return clientService.getAllClients();
    }

    private Set<Rent> getAllRents() throws SQLException {
        return rentService.getAllRents();
    }

}

