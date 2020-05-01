package Model.Statements;

import Model.ADT.MyIDictionary;
import Model.Expressions.Exp;
import Model.MyException;
import Model.PrgState;
import Model.Types.IntType;
import Model.Types.StringType;
import Model.Types.Type;
import Model.Values.IntValue;
import Model.Values.StringValue;
import Model.Values.Value;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class ReadFile implements IStmt {
    Exp exp;
    String var_name;

    public ReadFile(Exp exp, String var_name) {
        this.exp = exp;
        this.var_name = var_name;
    }

    @Override
    public String toString() {
        return "Reading "+this.exp.toString()+" - "+this.var_name;
    }

    @Override
    public MyIDictionary<String, Type> typecheck(MyIDictionary<String, Type> typeEnv) throws MyException {
        Type typeExp = this.exp.typecheck(typeEnv);
        Type typeVar = typeEnv.getValue(this.var_name);
        if (!typeVar.equals(new StringType()))
            throw new MyException("Opening file not string type");
        return typeEnv;
    }

    @Override
    public PrgState execute(PrgState state) throws MyException {
        MyIDictionary<StringValue, BufferedReader> filetbl=state.getFileTable();
        MyIDictionary<String, Value> symTbl=state.getSymTable();
        MyIDictionary<Integer, Value> heap = state.getHeap();
        Value val=exp.eval(symTbl,heap);
        if(symTbl.isDefined(this.var_name) && symTbl.getValue(this.var_name).getType().equals(new IntType())) {
            Value file=this.exp.eval(symTbl,heap);
            if(file.getType().equals(new StringType())){
                BufferedReader reader=filetbl.getValue((StringValue)file);
                if(reader!=null){
                    try{
                        String line=reader.readLine();
                        IntValue intVal;
                        if(line==null){
                            intVal=new IntValue(0);
                        }else{
                            intVal=new IntValue(Integer.parseInt(line));
                        }
                        symTbl.update(this.var_name,intVal);
                    }
                    catch (IOException ioe){
                        throw new MyException(ioe.getMessage());
                    }
                }else{
                    throw new MyException("No opened file with this name");

                }
            }else{
                throw new MyException("Filename expected StringType");
            }

        }else{
            throw new MyException("Variable not defined or expected IntType");
        }

        return null;

    }
}
