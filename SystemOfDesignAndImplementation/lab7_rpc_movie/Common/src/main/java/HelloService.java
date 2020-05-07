import java.util.concurrent.Future;

public interface HelloService {
    Future<String> send(String head, String body);
}
