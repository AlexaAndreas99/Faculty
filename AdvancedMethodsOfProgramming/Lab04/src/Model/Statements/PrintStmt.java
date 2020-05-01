package Model.Statements;
import Model.ADT.*;
import Model.Expressions.*;
import Model.MyException;
import Model.PrgState;
import Model.Types.Type;
import Model.Values.Value;

public class PrintStmt implements IStmt {
    private Exp exp;


    public PrintStmt(Exp e){exp=e;}
    @Override
    public String toString(){return "print("+exp.toString()+")";}

    @Override
    public MyIDictionary<String, Type> typecheck(MyIDictionary<String, Type> typeEnv) throws MyException {
        Type typ = exp.typecheck(typeEnv);
        return typeEnv;
    }

    @Override
    public PrgState execute(PrgState state) throws MyException {
        MyIList<Value> out1=state.getOut();
        MyIDictionary<String,Value>   symTable=state.getSymTable();
        MyIDictionary<Integer, Value> heap = state.getHeap();
        out1.add(exp.eval(symTable,heap));
        return null;
    }
}
