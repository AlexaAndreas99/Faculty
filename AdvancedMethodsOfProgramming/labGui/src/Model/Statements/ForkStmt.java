package Model.Statements;

import Model.ADT.MyDictionary;
import Model.ADT.MyIDictionary;
import Model.ADT.MyStack;
import Model.MyException;
import Model.PrgState;
import Model.Types.Type;
import Model.Values.Value;

import java.util.Map;

public class ForkStmt implements IStmt {
    private IStmt stmt;

    @Override
    public String toString() {
        return "fork("+this.stmt.toString()+")";
    }

    public ForkStmt(IStmt stmt) {
        this.stmt = stmt;
    }

    @Override
    public MyIDictionary<String, Type> typecheck(MyIDictionary<String, Type> typeEnv) throws MyException {
        this.stmt.typecheck(typeEnv);
        return typeEnv;
    }

    @Override
    public PrgState execute(PrgState state) throws MyException {

        MyIDictionary<String, Value> newSymTable = new MyDictionary<>();
        for (Map.Entry<String, Value> entry : state.getSymTable().getDict().entrySet())
            newSymTable.update(entry.getKey(), entry.getValue().deepCopy());


        PrgState newPrg = new PrgState(new MyStack<>(),newSymTable,state.getOut(),state.getFileTable(),state.getHeap(),this.stmt);

        newPrg.setNewId();
        return newPrg;
    }
}
