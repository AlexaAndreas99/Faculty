//import domain.*;
//import ui.Console;
//import java.io.IOException;
//import java.io.PrintWriter;
//import java.net.InetSocketAddress;
//import java.net.ServerSocket;
//import java.net.Socket;
//import java.net.SocketAddress;
//import java.util.Scanner;
//import java.util.concurrent.ExecutorService;
//import java.util.concurrent.Executors;
//
//public class Main {
//    public static void main(String args[]) {
//        Socket client = new Socket();
//        SocketAddress address = new InetSocketAddress(10005);
//        ExecutorService executor = Executors.newFixedThreadPool(Runtime.getRuntime().availableProcessors());
//        try {
//            client.connect(address);
//            Scanner scanner = new Scanner(System.in);
//            Scanner in = new Scanner(client.getInputStream());
//            PrintWriter out = new PrintWriter(client.getOutputStream(), true);
//            executor.execute(new Sender(out));
//            executor.execute(new Receiver(in));
//            System.out.println("ok done");
//        } catch (IOException e) {
//            e.printStackTrace();
//        }
//
//        /*
//        Validator<Movie> movieValidator = new MovieValidator();
//        Validator<Client> clientValidator = new ClientValidator();
//        Validator<Rent> rentValidator = new RentValidator();
//
//        Repository<Long, Movie> movieRepository = new MovieFileRepository(movieValidator, "./data/movies");
//        Repository<Long, Client> clientRepository = new ClientFileRepository(clientValidator, "./data/clients");
//        Repository<Long, Rent> rentRepository = new RentFileRepository(rentValidator, "./data/rents");
//
//        Repository<Long,Movie> dbMovieRepository = new DBClientRepository<>();
//        MovieService movieService = new MovieService(dbMovieRepository);
//
//        //MovieService movieService = new MovieService(movieRepository);
//        ClientService clientService = new ClientService(clientRepository);
//        RentService rentService = new RentService(rentRepository);
//
//        Console console = new Console(movieService, clientService, rentService);
//        console.runConsole();
//
//        System.out.println("Hello World!");
//        */
//    }
//
//}
