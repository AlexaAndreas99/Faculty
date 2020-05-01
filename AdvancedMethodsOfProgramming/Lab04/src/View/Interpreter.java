package View;

import Model.ADT.*;
import Model.Expressions.ArithExp;
import Model.Expressions.ValueExp;
import Model.Expressions.VarExp;
import Model.PrgState;
import Model.Statements.*;
import Model.Types.BoolType;
import Model.Types.IntType;
import Model.Values.BoolValue;
import Model.Values.IntValue;
import Model.Values.StringValue;
import Model.Values.Value;
import Repository.*;
import Controller.Controller;

import java.io.BufferedReader;

class Interpreter {
    public static void main(String[] args) {
        IStmt ex1 = new CompStmt(new VarDeclStmt("v", new IntType()), new CompStmt(new AssignStmt("v", new ValueExp(new IntValue(2))), new PrintStmt(new VarExp("v"))));;
        IStmt ex2 = new CompStmt( new VarDeclStmt("a",new IntType()),new CompStmt(new VarDeclStmt("b",new IntType()),
                new CompStmt(new AssignStmt("a", new ArithExp('+',new ValueExp(new IntValue(2)),new
                        ArithExp('*',new ValueExp(new IntValue(3)), new ValueExp(new IntValue(5))))),
                        new CompStmt(new AssignStmt("b",new ArithExp('+',new VarExp("a"), new
                                ValueExp(new IntValue(1)))), new PrintStmt(new VarExp("b"))))));
        IStmt ex3 = new CompStmt(new VarDeclStmt("a",new BoolType()),
                new CompStmt(new VarDeclStmt("v", new IntType()),
                        new CompStmt(new AssignStmt("a", new ValueExp(new BoolValue(true))),
                                new CompStmt(new IfStmt(new VarExp("a"),new AssignStmt("v",new ValueExp(new
                                        IntValue(2))), new AssignStmt("v", new ValueExp(new IntValue(3)))), new PrintStmt(new
                                        VarExp("v"))))));

        PrgState prg1 = new PrgState(new MyStack<IStmt>(), new MyDictionary<String, Value>(), new MyList<Value>(), new MyDictionary<StringValue, BufferedReader>(),new MyDictionary<Integer, Value>(), ex1);
        Container repo1 = new Repository(prg1, "log1.txt");
        Controller ctr1 = new Controller(repo1);

        PrgState prg2 = new PrgState(new MyStack<IStmt>(), new MyDictionary<String, Value>(), new MyList<Value>(), new MyDictionary<StringValue, BufferedReader>(),new MyDictionary<Integer, Value>(), ex2);
        Container repo2 = new Repository(prg2,"log2.txt");
        Controller ctr2 = new Controller(repo2);

        PrgState prg3 = new PrgState(new MyStack<IStmt>(), new MyDictionary<String, Value>(), new MyList<Value>(), new MyDictionary<StringValue, BufferedReader>(),new MyDictionary<Integer, Value>(), ex3);
        Container repo3 = new Repository(prg3,"log3.txt");
        Controller ctr3 = new Controller(repo3);
        TextMenu menu = new TextMenu();
        menu.addCommand(new ExitCommand("0", "exit"));
        menu.addCommand(new RunExample("1", ex1.toString(), ctr1));
         menu.addCommand(new RunExample("2",ex2.toString(),ctr2));
        menu.addCommand(new RunExample("3",ex3.toString(),ctr3));
        menu.show();
    }
}
