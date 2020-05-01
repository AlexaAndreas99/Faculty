package Model.Types;

import Model.Values.*;

public class RefType implements Type {
    Type inner;

    public RefType(Type inner) {
        this.inner = inner;
    }

    public Type getInner() {
        return inner;
    }

    @Override
    public Type deepCopy() {
        return new RefType(this.inner);
    }

    @Override
    public boolean equals(Object obj) {
        if( obj instanceof RefType)
            return inner.equals(((RefType) obj).getInner());
        else
            return false;
    }

    @Override
    public String toString() {
        return "Ref("+inner.toString()+")";
    }

    @Override
    public Value defaultValue() {
        return new RefValue(0,inner);
    }

}
