package Model.Statements;

import Model.ADT.MyIDictionary;
import Model.Expressions.Exp;
import Model.MyException;
import Model.PrgState;
import Model.Types.StringType;
import Model.Types.Type;
import Model.Values.StringValue;
import Model.Values.Value;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class OpenRFile implements IStmt {

    Exp exp;

    @Override
    public String toString() {
        return "Opening "+this.exp;
    }

    public OpenRFile(Exp e) {
        this.exp = e;
    }

    @Override
    public MyIDictionary<String, Type> typecheck(MyIDictionary<String, Type> typeEnv) throws MyException {
        Type type = this.exp.typecheck(typeEnv);
        if (!type.equals(new StringType()))
            throw new MyException("Name of closing file not string type");
        return typeEnv;

    }

    @Override
    public PrgState execute(PrgState state) throws MyException {

        MyIDictionary<StringValue, BufferedReader> filetbl=state.getFileTable();
        MyIDictionary<String,Value> symTbl=state.getSymTable();
        MyIDictionary<Integer, Value> heap = state.getHeap();
        Value val=exp.eval(symTbl,heap);
        if(!(val.getType()instanceof StringType))
            throw new MyException("Expected String!");
        else if(filetbl.isDefined((StringValue) val))
            throw  new MyException("Already defined!");
        else
        {
            try{
                String filenameStringValue=((StringValue)val).getVal();
                BufferedReader br=new BufferedReader(new FileReader(filenameStringValue));
                filetbl.update((StringValue)val,br);
            }catch(IOException ioe){
                throw  new MyException(ioe.getMessage());
            }
        }
        return null;

    }
}
