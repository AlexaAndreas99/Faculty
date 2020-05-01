package Model.Expressions;

import Model.ADT.MyIDictionary;
import Model.MyException;
import Model.Types.Type;
import Model.Values.Value;

public class VarExp implements Exp {
    String id;

    @Override
    public String toString() {
        return id;
    }

    public VarExp(String i){id=i;}

    @Override
    public Type typecheck(MyIDictionary<String, Type> typeEnv) throws MyException {
        return typeEnv.getValue(id);
    }

    @Override
    public Value eval(MyIDictionary<String, Value> tbl,MyIDictionary<Integer,Value> heap) throws MyException {
        return tbl.getValue(id);

    }
}
