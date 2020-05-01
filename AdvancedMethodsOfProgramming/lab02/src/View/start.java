package View;

import Model.*;
import Repository.*;
import Controller.*;
import Exception.AutoException;


public class start {

    public static void main(String [] a)
    {
        Automobile auto= new Car(1002,"asd");
        Automobile auto1= new Bike(3,"qwe");
        Automobile auto2= new Truck(1004,"rty");
        Automobile auto3= new Truck(0,"jkl");
        Container c=new Repo(3);
        Ctrl ctrl=new Ctrl(c);
        //add tests
        try{
             ctrl.add(auto);
             ctrl.add(auto1);
             ctrl.add(auto2);
             ctrl.add(auto3);
             assert true;
        }catch (AutoException e){
            System.out.println(e.getMessage()+","+" the maximum size is: "+c.size());
            assert false;
        }
        // remove tests
        try{
            ctrl.remove(auto3);
            assert true;
        }catch (AutoException e)
        {
            System.out.println(e.getMessage()+"\n");
            assert false;
        }
        //remove tests
        try{
            ctrl.remove(auto2);
            assert true;
        }catch (AutoException e)
        {
            System.out.println(e.getMessage());
            assert false;
        }
        // greater tests
        int n=4;
        assert ctrl.get_greater(n).length==1;
        System.out.println("The cars prices larger than "+ n +" are:");
        for( Automobile i: ctrl.get_greater(n))
        System.out.println(i);

        System.out.println("\nThe car list: ");
        for(Automobile i:ctrl.get_all())
            System.out.println(i);
    }
}
