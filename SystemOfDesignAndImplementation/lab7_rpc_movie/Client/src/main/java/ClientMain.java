import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class ClientMain {
    public static void main(String args[]) {
        TcpClient tcp = new TcpClient();
        ExecutorService executorService =Executors.newFixedThreadPool(Runtime.getRuntime().availableProcessors());
        HelloService helloService = new HelloServiceClient(executorService,tcp);
        console console = new console(helloService);
        console.run();
    }


}