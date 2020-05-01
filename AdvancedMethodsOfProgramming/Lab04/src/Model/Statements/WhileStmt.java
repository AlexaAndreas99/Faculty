package Model.Statements;

import Model.ADT.MyIDictionary;
import Model.ADT.MyIStack;
import Model.Expressions.Exp;
import Model.MyException;
import Model.PrgState;
import Model.Types.BoolType;
import Model.Types.Type;
import Model.Values.BoolValue;
import Model.Values.Value;

public class WhileStmt implements IStmt {
    Exp exp;
    IStmt st;
    public WhileStmt(Exp e, IStmt t){exp=e;st=t;}

    public String toString(){return "While("+exp.toString()+") "+exp.toString();}

    @Override
    public MyIDictionary<String, Type> typecheck(MyIDictionary<String, Type> typeEnv) throws MyException {
        Type typeExpr = this.exp.typecheck(typeEnv);
        if (!typeExpr.equals(new BoolType()))
            throw new MyException("Condition of IF not bool type");
        this.st.typecheck(typeEnv);
        return typeEnv;
    }

    @Override
    public PrgState execute(PrgState state) throws MyException {
        MyIStack<IStmt> stack = state.getExeStack();
        MyIDictionary<String, Value> dict = state.getSymTable();
        MyIDictionary<Integer, Value> heap = state.getHeap();
        Value v = exp.eval(dict,heap);
        if(exp.eval(dict,heap).getType().equals(new BoolType()))
            if(((BoolValue)v).getVal()) {
                stack.push(new WhileStmt(exp,st));
                stack.push(st);
            }
            else
                return null;
        else
            throw new MyException("Expected Bool!");

        return null;
    }
}
