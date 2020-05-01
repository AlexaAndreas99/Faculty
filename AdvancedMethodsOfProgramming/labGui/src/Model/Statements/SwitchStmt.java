package Model.Statements;

import Model.ADT.MyIDictionary;
import Model.ADT.MyIStack;
import Model.Expressions.Exp;
import Model.Expressions.RelExp;
import Model.MyException;
import Model.PrgState;
import Model.Types.IntType;
import Model.Types.Type;
import Model.Values.Value;

public class SwitchStmt implements IStmt {
   private IStmt st1,st2,st3;
   private Exp e1,e2,e3;

    public SwitchStmt(IStmt st1, IStmt st2, IStmt st3, Exp e1, Exp e2, Exp e3) {
        this.st1 = st1;
        this.st2 = st2;
        this.st3 = st3;
        this.e1 = e1;
        this.e2 = e2;
        this.e3 = e3;
    }

    @Override
    public PrgState execute(PrgState state) throws MyException {
        MyIStack<IStmt> stack = state.getExeStack();
        MyIDictionary<String, Value> dict = state.getSymTable();
        MyIDictionary<Integer, Value> heap = state.getHeap();

        IStmt ni=new IfStmt(new RelExp("==",e1,e2),st1,new IfStmt(new RelExp("==",e1,e3),st2,st3));
        stack.push(ni);
        return null;
    }

    @Override
    public MyIDictionary<String, Type> typecheck(MyIDictionary<String, Type> typeEnv) throws MyException {

        Type typee1=e1.typecheck(typeEnv);
        Type typee2=e2.typecheck(typeEnv);
        Type typee3=e3.typecheck(typeEnv);

        if(typee1 instanceof IntType&&typee2 instanceof IntType&&typee3 instanceof IntType) {

            st1.typecheck(typeEnv);
            st2.typecheck(typeEnv);
            st3.typecheck(typeEnv);
        }
        else throw new MyException("Some exp are not of type int");

        return typeEnv;
    }

    @Override
    public String toString() {
        return "switch( "+e1.toString()+") "+
                "case( "+e2.toString()+"): "+st1.toString()+
                "case( "+e3.toString()+"): "+st2.toString()+
                "default: "+st3.toString()
                ;
    }
}
