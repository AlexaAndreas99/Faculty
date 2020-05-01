package Model.Expressions;

import Model.ADT.MyIDictionary;
import Model.MyException;
import Model.Types.BoolType;
import Model.Types.IntType;
import Model.Types.Type;
import Model.Values.BoolValue;
import Model.Values.IntValue;
import Model.Values.Value;

public class RelExp implements Exp {
    Exp e1;
    Exp e2;
    String op;

    public RelExp(String o,Exp e11,Exp e22){e1=e11;e2=e22;op=o;}

    @Override
    public String toString() {
        return String.valueOf(e1)+op+String.valueOf(e2);
    }

    public Type typecheck(MyIDictionary<String,Type> typeEnv) throws MyException{
        Type typ1, typ2;
        typ1=e1.typecheck(typeEnv);
        typ2=e2.typecheck(typeEnv);
        if (typ1.equals(new IntType())) {
            if (typ2.equals(new IntType())) {
                return new BoolType();
            } else
                throw new MyException("second operand is not an integer");
        }else
            throw new MyException("first operand is not an integer");
    }
    @Override
    public Value eval(MyIDictionary<String, Value> tbl,MyIDictionary<Integer,Value> heap) throws MyException {
        Value v1, v2;
        v1 = this.e1.eval(tbl,heap);
        if (v1.getType().equals(new IntType())) {
            v2 = this.e2.eval(tbl,heap);
            if (v2.getType().equals(new IntType())) {
                IntValue i1 = (IntValue) v1;
                IntValue i2 = (IntValue) v2;
                int n1,n2;
                n1=i1.getVal();
                n2=i2.getVal();
                if(op=="<") return new BoolValue(n1<n2);
                if(op=="<=") return new BoolValue(n1<=n2);
                if(op==">") return new BoolValue(n1>n2);
                if(op==">=") return new BoolValue(n1>=n2);
                if(op=="==") return new BoolValue(n1==n2);
                if(op=="!=") return new BoolValue(n1!=n2);

            }else
                throw new MyException("Second operand is not an integer");
        }else
            throw new MyException("First operand is not an integer");
        return new BoolValue(false);
    }
}