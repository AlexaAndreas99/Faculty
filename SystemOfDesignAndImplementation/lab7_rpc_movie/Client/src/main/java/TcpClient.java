import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.net.Socket;
import java.net.SocketAddress;

public class TcpClient {
    public Message sendAndReceive(Message request){

        Socket client = new Socket();
        SocketAddress address = new InetSocketAddress(10005);

        try {
            client.connect(address);
            InputStream is = client.getInputStream();
            OutputStream os = client.getOutputStream();

        System.out.println("Sending request...");
        request.writeTo(os);
        System.out.println("Waiting for response...");
        Message response = new Message();
        response.readFrom(is);
        System.out.println(response.toString());
        return response;
        } catch (IOException e) {
            e.printStackTrace();
        }
        return new Message();
    }
}
