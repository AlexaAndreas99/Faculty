package Model.Expressions;

import Model.ADT.MyIDictionary;
import Model.MyException;
import Model.Types.Type;
import Model.Values.Value;

public class ValueExp implements Exp {
    Value e;

    @Override
    public String toString() {
        return String.valueOf(e);
    }

    public ValueExp(Value e1){e=e1;}

    @Override
    public Type typecheck(MyIDictionary<String, Type> typeEnv) throws MyException {
        return e.getType();
    }

    @Override
    public Value eval(MyIDictionary<String, Value> tbl,MyIDictionary<Integer,Value> heap) throws MyException {
        return e;
    }
}
