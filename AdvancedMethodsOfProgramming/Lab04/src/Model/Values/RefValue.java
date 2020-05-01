package Model.Values;

import Model.Types.RefType;
import Model.Types.Type;

public class RefValue implements Value{
    int address;
    Type locationType;

    @Override
    public Value deepCopy() {
        return new RefValue(this.address,this.locationType.deepCopy());
    }

    public int getAddress() {
        return address;
    }

    public RefValue(int address, Type locationType) {
        this.address = address;
        this.locationType = locationType;
    }

    public Type getLocationType() {
        return locationType;
    }

    @Override
    public boolean equals(Object obj) {
        if( obj instanceof RefValue)
            return this.address==((RefValue) obj).getAddress()&&
                    this.locationType.equals(obj);
        else
            return false;
    }

    @Override
    public String toString() {
        return "("+Integer.toString(this.address)+","+this.locationType.toString()+")";
    }

    @Override
    public Type getType() {
        return new RefType(locationType);
    }

    public void setAddress(int address) {
        this.address = address;
    }
}
