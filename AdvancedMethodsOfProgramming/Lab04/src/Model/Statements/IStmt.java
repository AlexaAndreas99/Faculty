package Model.Statements;
import Model.*;
import Model.ADT.MyIDictionary;
import Model.Types.Type;

public interface IStmt {
    PrgState execute(PrgState state) throws MyException;
    MyIDictionary<String,Type> typecheck(MyIDictionary<String, Type> typeEnv) throws MyException;
}
