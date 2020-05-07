

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

class Run implements Runnable{
    ServerSocket socket;
    ServerConnection conn;
    Run(ServerSocket socket, ServerConnection conn) {
        this.socket = socket;
        this.conn = conn;
    }

    @Override
    public void run() {
        while(true) {
            try {
                Socket client = socket.accept();
                System.out.println("connected");
                conn.handleClient(client);
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
}
public class ServerConnection {
    ServerSocket socket;
    ExecutorService executor = Executors.newFixedThreadPool(Runtime.getRuntime().availableProcessors());

    ServerConnection () {
        try {
            socket = new ServerSocket(10005);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    public void handleClient(Socket client) {
        InputStream in;
        OutputStream out;
        try {
            in = client.getInputStream();
            out = client.getOutputStream();
            ClientHandler c = new ClientHandler(in,out);
            c.run();

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    public void runServer() {
        executor.submit(new Run(socket, this));
    }
}
