package View;

import Controller.Controller;
import Model.MyException;

public class RunExample extends Command {
    private Controller ctrl;

    public RunExample(String key, String description, Controller ctrl) {
        super(key, description);
        this.ctrl = ctrl;
    }

    @Override
    public void execute() {
        try {
            this.ctrl.allStep();
        }
        catch( InterruptedException me) {
            System.out.println(me.getMessage());
        }
    }
}