package Model.Values;
import Model.Types.BoolType;
import Model.Types.Type;

public class BoolValue implements Value {

    private boolean val;

    @Override
    public boolean equals(Object obj) {
        return obj instanceof BoolValue;
    }

    public BoolValue(boolean v){this.val=v;}
    @Override
    public Type getType() {
        return new BoolType();
    }

    @Override
    public Value deepCopy() {
        return new BoolValue(this.val);
    }

    public boolean getVal(){return this.val;}
    public String toString(){return Boolean.toString(this.val);}

}
