package View;

import Controller.Controller;
import Model.ADT.*;
import Model.Expressions.*;
import Model.MyException;
import Model.PrgState;
import Model.Statements.*;
import Model.Types.*;
import Model.Values.BoolValue;
import Model.Values.IntValue;
import Model.Values.StringValue;
import Model.Values.Value;
import Repository.Container;
import Repository.Repository;

import java.io.BufferedReader;
import java.util.Arrays;

public class start {


    private static IStmt concatStatements(IStmt... statements) {
        if (statements.length == 1)
            return statements[0];

        return new CompStmt(statements[0], concatStatements(Arrays.copyOfRange(statements, 1, statements.length)));
    }

    public static void main(String[] a) {





        // int v; Ref int a; fork(v=10; print(v)); fork(new(a, 20); print(Rh(a))); print(v); print(Rh(a));

        //System.out.println(ex11.toString());

//        MyIStack<IStmt> stack = new MyStack<IStmt>();
//        MyIDictionary<String, Value> symTable = new MyDictionary<String, Value>();
//        MyIList<Value> out = new MyList<Value>();
//        MyIDictionary<StringValue, BufferedReader> FileTable = new MyDictionary<StringValue, BufferedReader>();
//        MyIDictionary<Integer, Value> heap = new MyDictionary<>();
//        PrgState state = new PrgState(stack, symTable, out, FileTable, heap, ex10dot1);
//        Container repo = new Repository(state, "./src/Repository/logFile.txt");
//        Controller ctrl = new Controller(repo);
//
//        System.out.println(ex10dot1.toString());
//
//
//        try {
//            ctrl.allStep();
//            System.out.println(out.toString());
//        } catch (InterruptedException e) {
//            System.out.println(e.getMessage());
//        }
    }
}