package Exception;

public class AutoException extends Exception{
    public AutoException(String msg) {
        super(msg);
    }

    @Override
    public String getMessage() {
        return super.getMessage();
    }
}
