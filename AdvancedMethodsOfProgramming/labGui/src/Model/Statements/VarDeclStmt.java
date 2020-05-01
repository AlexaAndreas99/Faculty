package Model.Statements;

import Model.ADT.MyDictionary;
import Model.ADT.MyIDictionary;
import Model.MyException;
import Model.PrgState;
import Model.Types.*;
import Model.Values.BoolValue;
import Model.Values.IntValue;
import Model.Values.StringValue;
import Model.Values.Value;

import java.util.Map;

public class VarDeclStmt implements IStmt {
    String name;
    Type type;

    @Override
    public String toString() {
        return String.valueOf(type)+" "+name;
    }

    public  VarDeclStmt(String s, Type t){name=s;type=t;}

    @Override
    public MyIDictionary<String, Type> typecheck(MyIDictionary<String, Type> typeEnv) throws MyException {
        MyIDictionary<String, Type> newEnv = new MyDictionary<>();
        for (Map.Entry<String, Type> entry : typeEnv.getDict().entrySet())
            newEnv.update(entry.getKey(), entry.getValue().deepCopy());

        newEnv.add(name,type);
        return newEnv;
    }

    @Override
    public PrgState execute(PrgState state) throws MyException {
        MyIDictionary<String, Value> symTable=state.getSymTable();
        if(!symTable.isDefined(this.name))
        {
            if(this.type instanceof IntType)
                symTable.update(this.name,new IntValue(0));

            if(this.type instanceof BoolType)
                symTable.update(this.name,new BoolValue(false));
            if(this.type instanceof StringType)
                symTable.update(this.name,new StringValue(""));
            if(this.type instanceof RefType) {
                //RefType c=(RefType)type;
                //Type x=c.getInner();
                //while(x instanceof RefType)
                //    x=c.getInner();
                symTable.update(this.name, type.defaultValue());
            }
        }
        else throw new MyException("Variable already declared!");
        return null;
    }
}
