package Model.Expressions;

import Model.ADT.MyIDictionary;
import Model.MyException;
import Model.Types.BoolType;
import Model.Types.IntType;
import Model.Types.Type;
import Model.Values.IntValue;
import Model.Values.BoolValue;
import Model.Values.Value;

public class LogicExp implements Exp {
    Exp e1;
    Exp e2;
    int op;//0=and,1=or
    LogicExp(Exp e3,Exp e4,int o){e1=e3;e2=e4;op=o;}

    @Override
    public Type typecheck(MyIDictionary<String,Type> typeEnv) throws MyException{
        Type typ1, typ2;
        typ1=e1.typecheck(typeEnv);
        typ2=e2.typecheck(typeEnv);
        if (typ1.equals(new BoolType())) {
            if (typ2.equals(new BoolType())) {
                return new BoolType();
            } else
                throw new MyException("second operand is not a bool");
        }else
            throw new MyException("first operand is not a bool");
    }

    @Override
    public Value eval(MyIDictionary<String, Value> tbl,MyIDictionary<Integer,Value> heap) throws MyException {
        Value v1, v2;
        v1 = this.e1.eval(tbl,heap);
        if (v1.getType().equals(new BoolType())) {
            v2 = this.e2.eval(tbl,heap);
            if (v2.getType().equals(new BoolType())) {
                BoolValue i1 = (BoolValue) v1;
                BoolValue i2 = (BoolValue) v2;
                boolean n1,n2;
                n1=i1.getVal();//replaced v with i
                n2=i2.getVal();
                if(op==0) return new BoolValue(n1&&n2);
                if(op==1) return new BoolValue(n1||n2);

            }else
                throw new MyException("Second operand is not an integer");
        }else
            throw new MyException("First operand is not an integer");
        return new BoolValue(false);
    }
}
