package Model.Expressions;

import Model.ADT.MyIDictionary;
import Model.MyException;
import Model.Types.RefType;
import Model.Types.Type;
import Model.Values.RefValue;
import Model.Values.Value;

public class ReadHeap implements Exp {
    private String var_name;
    private Exp exp;

    @Override
    public String toString() {
        return "ReadHeap("+String.valueOf(exp)+")";
    }

    public Type typecheck(MyIDictionary<String,Type> typeEnv) throws MyException{
        Type typ=exp.typecheck(typeEnv);
        if (typ instanceof RefType) {
            RefType reft =(RefType) typ;
            return reft.getInner();
        } else
            throw new MyException("the rH argument is not a Ref Type");
    }

    @Override
    public Value eval(MyIDictionary<String, Value> tbl, MyIDictionary<Integer, Value> heap) throws MyException {
        Value addr=tbl.getValue(var_name);
        Value v=exp.eval(tbl,heap);
        if(!(v instanceof RefValue))
            throw new MyException("The variable is not a RefValue!");
        RefValue vv=(RefValue)v;
        int i=vv.getAddress();
        if(!heap.isDefined(i))
            throw new MyException("The address is invalid!");
        else
            return heap.getValue(i);
    }

    public ReadHeap(Exp e) {
        this.exp = e;
    }
}
