package Model.Statements;

import Model.ADT.MyIDictionary;
import Model.ADT.MyIHeap;
import Model.ADT.MyIStack;
import Model.Expressions.Exp;
import Model.MyException;
import Model.PrgState;
import Model.Types.RefType;
import Model.Types.Type;
import Model.Values.IntValue;
import Model.Values.RefValue;
import Model.Values.Value;



public class NewStmt implements IStmt {
    private String var_name;
    private Exp exp;

    public NewStmt(String var_name, Exp exp) {
        this.var_name = var_name;
        this.exp = exp;
    }

    @Override
    public String toString() {
        return "new("+this.var_name+","+this.exp.toString()+")";
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
        MyIDictionary<Integer,Value> heap=state.getHeap();
        Value v=exp.eval(dict,heap);
//        if(dict.isDefined(var_name)&&dict.getValue(var_name).getType() instanceof RefType) {
//            Type c=dict.getValue(var_name).getType();
//            if (c.equals(v)) {
//                RefValue z = new RefValue(heap.add(v), c);
//                dict.update(var_name, z);
//            } else
//                throw new MyException("The types are not equal!");
//        }
//        else
//            throw new MyException("The variable is not defined or it's not a ref type");

        int i=1;
        while(true){
            if(heap.isDefined(i))
                i++;
            else
            break;
        }
        //Type c=dict.getValue(var_name).getType();
        //if (!c.equals(v))
        //    throw new MyException("Type are not the same!");

        if(!dict.isDefined(var_name)){
            throw new MyException("Variable not defined!");
        }
        if(!(dict.getValue(var_name).getType() instanceof RefType))
            throw new MyException("Variable not of RefType!");
        if(!v.getType().equals(((RefValue)dict.getValue(var_name)).getLocationType()))
            throw new MyException("Variable Type doesnt match location type");
        heap.update(i,v);
        dict.update(var_name,new RefValue(i,v.getType()));

        return null;
    }
}
