import java.util.concurrent.ExecutorService;
import java.util.concurrent.Future;

public class HelloServiceClient implements HelloService{
    private ExecutorService executorService;
    private TcpClient tcpClient;

    public HelloServiceClient(ExecutorService executorService, TcpClient tcpClient) {
        this.executorService = executorService;
        this.tcpClient = tcpClient;
    }

    @Override
    public Future<String> send(String head, String body) {

        return executorService.submit(()->{
           Message request =new Message(head,body);
           Message response = tcpClient.sendAndReceive(request);
            //System.out.println("Received response: \n"+response.toString());
            return response.getBody();
        });

    }

}
