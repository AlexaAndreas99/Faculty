package Model.Expressions;

import Model.ADT.MyIDictionary;
import Model.MyException;
import Model.Types.Type;
import Model.Values.Value;

public interface Exp {
    Value eval(MyIDictionary<String,Value> tbl,MyIDictionary<Integer,Value> heap)throws MyException;
    Type typecheck(MyIDictionary<String, Type> typeEnv) throws MyException;
}
