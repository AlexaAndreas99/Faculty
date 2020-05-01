package Model.Statements;

import Model.ADT.MyIDictionary;
import Model.Expressions.Exp;
import Model.MyException;
import Model.PrgState;
import Model.Types.RefType;
import Model.Types.Type;
import Model.Values.RefValue;
import Model.Values.Value;

public class WriteHeap implements IStmt {
    String var_name;
    Exp exp;

    public WriteHeap(String var_name, Exp exp) {
        this.var_name = var_name;
        this.exp = exp;
    }

    @Override
    public String toString() {
        return "WriteHeap("+this.var_name+","+this.exp.toString()+")";
    }

    @Override
    public MyIDictionary<String, Type> typecheck(MyIDictionary<String, Type> typeEnv) throws MyException {
        Type typevar = typeEnv.getValue(var_name);
        Type typexp = exp.typecheck(typeEnv);
        if (typevar.equals(new RefType(typexp)))
            return typeEnv;
        else
            throw new MyException("Assignment: right hand side and left hand side have different types ");
    }

    @Override
    public PrgState execute(PrgState state) throws MyException {
        MyIDictionary<String, Value> dict = state.getSymTable();
        MyIDictionary<Integer, Value> heap = state.getHeap();
        Value v = exp.eval(dict,heap);
        if(!dict.isDefined(var_name))
            throw new MyException("Variable not defined!");
        else
            if(!(dict.getValue(var_name).getType() instanceof RefType))
                throw new MyException("Variable not of RefType!");
            else
            {
                Value x=dict.getValue(var_name);
                RefValue y=(RefValue)x;
                int i=y.getAddress();
                if(!heap.isDefined(i))
                    throw new MyException("The key associated with the variable is not defined in heap!");
                else
                    if(!v.getType().equals(((RefValue)dict.getValue(var_name)).getLocationType()))
                        throw new MyException("Variable Type doesnt match location type");
                    else
                        heap.update(i,v);

            }

        return null;
    }
}
