import java.io.*;

public class Message {
    public static final int PORT = 10005;
    public static final String HOST = "localhost";

    private String header;
    private String body;

    public Message() {
    }

    public Message(String header, String body) {
        this.header = header;
        this.body = body;
    }

    public String getHeader() {
        return header;
    }

    public String getBody() {
        return body;
    }

    public void writeTo(OutputStream os) throws IOException{
        os.write((header+System.lineSeparator()+body+System.lineSeparator()).getBytes());
    }
    public void readFrom(InputStream is) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(is));
        header = br.readLine();
        body = br.readLine();
    }
    @Override
    public String toString() {
        return "Message{" +
                "header='" + header + '\'' +
                ", body='" + body + '\'' +
                '}';
    }
}
