package Model.Types;

import Model.Values.IntValue;
import Model.Values.Value;

public class IntType implements Type{

    @Override
    public Type deepCopy() {
        return new IntType();
    }

    @Override
    public Value defaultValue() {
        return new IntValue(0);
    }

    public boolean equals(Object another){
        return another instanceof IntType;
    }
    public String toString(){
        return "int";}
}
