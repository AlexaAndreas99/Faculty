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

public class closeRFile implements IStmt{
    Exp exp;

    public closeRFile(Exp exp) {
        this.exp = exp;
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
        MyIDictionary<String, Value> symTbl=state.getSymTable();
        MyIDictionary<Integer, Value> heap = state.getHeap();
        Value file=exp.eval(symTbl,heap);
        if(file.getType()instanceof StringType) {
            BufferedReader reader = filetbl.getValue((StringValue) file);
            if (reader != null) {
                try {
                    reader.close();
                    filetbl.remove((StringValue) file);

                } catch (IOException ioe) {
                    throw new MyException(ioe.getMessage());
                }
            } else {
                throw new MyException("File not opened!");
            }
        }else{
            throw new MyException("Expected StringType!");
        }
        return null;

    }

    @Override
    public String toString() {
        return "Closing "+this.exp;
    }
}
