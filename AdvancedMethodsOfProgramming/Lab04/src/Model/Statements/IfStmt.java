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

public class IfStmt implements IStmt {
Exp exp;
IStmt thenS;
IStmt elseS;
public IfStmt(Exp e, IStmt t, IStmt el){exp=e;thenS=t;elseS=el;}
public String toString(){return "IF("+exp.toString()+") THEN("+thenS.toString()+")ELSE("+elseS.toString()+")";}

    @Override
    public MyIDictionary<String, Type> typecheck(MyIDictionary<String, Type> typeEnv) throws MyException {
        Type typexp=exp.typecheck(typeEnv);
        if (typexp.equals(new BoolType())) {
            MyIDictionary<String,Type> thenEnv, elseEnv;
            thenEnv = thenS.typecheck(typeEnv);
            elseEnv = elseS.typecheck(typeEnv);
            return typeEnv;
        }
        else
            throw new MyException("The condition of IF has not the type bool");
    }

    @Override
    public PrgState execute(PrgState state) throws MyException {
        MyIStack<IStmt> stack = state.getExeStack();
        MyIDictionary<String, Value> dict = state.getSymTable();
        MyIDictionary<Integer, Value> heap = state.getHeap();
        Value v = exp.eval(dict,heap);

        if(exp.eval(dict,heap).getType().equals(new BoolType()))
            if(((BoolValue)v).getVal())
                stack.push(thenS);
            else
                stack.push(elseS);

        else
            throw new MyException("Expected Bool!");

        return null;
    }
}
