package Model.Statements;

import Model.ADT.MyIDictionary;
import Model.ADT.MyIStack;
import Model.Expressions.Exp;
import Model.Expressions.ValueExp;
import Model.MyException;
import Model.PrgState;
import Model.Types.Type;
import Model.Values.Value;

public class AssignStmt implements IStmt {
    String id;
    Exp exp;

    public AssignStmt(String v, Exp valueExp) {id=v;exp=valueExp;}

    public String toString(){ return id+"="+ exp.toString();}

    @Override
    public MyIDictionary<String, Type> typecheck(MyIDictionary<String, Type> typeEnv) throws MyException {
        Type typevar = typeEnv.getValue(id);
        Type typexp = exp.typecheck(typeEnv);
        if (typevar.equals(typexp))
            return typeEnv;
        else
            throw new MyException("Assignment: right hand side and left hand side have different types ");
    }

    @Override
    public PrgState execute(PrgState state) throws MyException {
        MyIStack<IStmt> stk = state.getExeStack();
        MyIDictionary<String, Value> symTbl=state.getSymTable();
        MyIDictionary<Integer, Value> heap = state.getHeap();
        Value val=exp.eval(symTbl,heap);
        if(symTbl.isDefined(id)){
            Type typeId=(symTbl.getValue(id)).getType();
            if(val.getType().equals(typeId))
                symTbl.update(id,val);
            else throw new MyException("declared type of variable "+id+" and type of the assigned expression do not match");
        }
        else throw new MyException("the used variable "+id+" was not declared before");
        return null;
    }
}
