package Model.Values;

import Model.Types.IntType;
import Model.Types.Type;

public class IntValue implements Value {
    private int val;

    public IntValue(int v){this.val=v;}
    @Override
    public Type getType() {
        return new IntType();
    }
    public int getVal(){return this.val;}

    @Override
    public Value deepCopy() {
        return new IntValue(this.val);
    }

    @Override
    public boolean equals(Object obj) {
        return obj instanceof IntValue;
    }

    public String toString(){return Integer.toString(this.val);}

}
