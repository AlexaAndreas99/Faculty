import domain.Client;
import domain.Movie;
import domain.Rent;
import domain.validators.ClientValidator;
import domain.validators.MovieValidator;
import domain.validators.RentValidator;
import domain.validators.Validator;
import repository.*;
import service.ClientService;
import service.MovieService;
import service.RentService;
import ui.Console;

public class Main {
    public static void main(String args[]) {

        Validator<Movie> movieValidator = new MovieValidator();
        Validator<Client> clientValidator = new ClientValidator();
        Validator<Rent> rentValidator = new RentValidator();

        Repository<Long, Movie> movieRepository = new MovieFileRepository(movieValidator, "./data/movies");
        Repository<Long, Client> clientRepository = new ClientFileRepository(clientValidator, "./data/clients");
        Repository<Long, Rent> rentRepository = new RentFileRepository(rentValidator, "./data/rents");

        Repository<Long,Movie> dbMovieRepository = new DBClientRepository<>();
        MovieService movieService = new MovieService(dbMovieRepository);

        //MovieService movieService = new MovieService(movieRepository);
        ClientService clientService = new ClientService(clientRepository);
        RentService rentService = new RentService(rentRepository);

        Console console = new Console(movieService, clientService, rentService);
        console.runConsole();

        System.out.println("Hello World!");
    }
}
