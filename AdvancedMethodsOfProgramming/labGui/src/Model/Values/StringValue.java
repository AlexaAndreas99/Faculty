package Model.Values;

import Model.Types.StringType;
import Model.Types.Type;

public class StringValue implements Value{
    String s;

    @Override
    public Value deepCopy() {
        return new StringValue(this.s);
    }

    @Override
    public boolean equals(Object obj) {
        return obj instanceof StringValue;
    }

    @Override
    public Type getType() {
        return new StringType();
    }

    public StringValue(String s1) {
        s=s1;
    }

    @Override
    public String toString() {
        return s;
    }
    public String getVal(){return s;}

}
