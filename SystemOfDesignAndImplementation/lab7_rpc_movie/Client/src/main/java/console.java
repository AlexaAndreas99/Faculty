import java.util.ArrayList;
import java.util.Scanner;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.Future;

public class console {
    HelloService helloService;
    ArrayList<String> commands;

    public console(HelloService helloService) {
        this.helloService = helloService;
        commands = new ArrayList<>();
        commands.add(0,"Add movie");
        commands.add(1,"Add client");
        commands.add(2,"Add rent");
        commands.add(3,"Delete movie");
        commands.add(4,"Delete client");
        commands.add(5,"Delete rent");
        commands.add(6,"Update movie");
        commands.add(7,"Update client");
        commands.add(8,"Print movies");
        commands.add(9,"Print clients");
        commands.add(10,"Print rents");
    }

    public void run() {

        while (true) {
            int i =this.menu();
            if(i==0)
                return;
            String head = commands.get(i-1);

            Scanner in = new Scanner(System.in);
            System.out.println("parameters: \n");
            String body = in.nextLine();
            Future<String> future = helloService.send(head, body);

            try {
                String result = future.get();
            } catch (InterruptedException | ExecutionException e) {
                e.printStackTrace();
            }
        }
    }
    private int menu(){
        Scanner in = new Scanner(System.in);
        System.out.println("0.Exit\n1.ADD Movie\nADD Client\n3.ADD Rent\n4.Delete Movie\n5.Delete Client\n6.Delete Rent\n7.Update Movie" +
                "\n8.Update Client\n9.Show all movies\n10.Show all clients\n11.Show all rents");
        return in.nextInt();
    }
}
