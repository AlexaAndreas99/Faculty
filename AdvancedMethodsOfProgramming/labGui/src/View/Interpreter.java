package View;

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
import Repository.*;
import Controller.Controller;

import java.io.BufferedReader;
import java.util.Arrays;

class Interpreter {

    private static IStmt concatStatements(IStmt... statements) {
        if (statements.length == 1)
            return statements[0];

        return new CompStmt(statements[0], concatStatements(Arrays.copyOfRange(statements, 1, statements.length)));
    }
    private static IStmt simpleEx(){return new CompStmt(new VarDeclStmt("v", new IntType()), new CompStmt(new AssignStmt("v", new ValueExp(new IntValue(2))), new PrintStmt(new VarExp("v"))));
    }
    private static IStmt arithEx(){return new CompStmt( new VarDeclStmt("a",new IntType()),new CompStmt(new VarDeclStmt("b",new IntType()),
            new CompStmt(new AssignStmt("a", new ArithExp('+',new ValueExp(new IntValue(2)),new
                    ArithExp('*',new ValueExp(new IntValue(3)), new ValueExp(new IntValue(5))))),
                    new CompStmt(new AssignStmt("b",new ArithExp('+',new VarExp("a"), new
                            ValueExp(new IntValue(1)))), new PrintStmt(new VarExp("b"))))));}
    private static IStmt ifEx(){return new CompStmt(new VarDeclStmt("a",new BoolType()),
            new CompStmt(new VarDeclStmt("v", new IntType()),
                    new CompStmt(new AssignStmt("a", new ValueExp(new BoolValue(true))),
                            new CompStmt(new IfStmt(new VarExp("a"),new AssignStmt("v",new ValueExp(new
                                    IntValue(2))), new AssignStmt("v", new ValueExp(new IntValue(3)))), new PrintStmt(new
                                    VarExp("v"))))));}
    private static IStmt fileEx(){return new CompStmt(new VarDeclStmt("varf", new StringType()), new CompStmt(new AssignStmt("varf", new ValueExp(new StringValue("./src/Repository/test.in"))),
            new CompStmt(new OpenRFile(new VarExp("varf")),
                    new CompStmt(new VarDeclStmt("varc", new IntType()),
                            new CompStmt(new ReadFile(new VarExp("varf"), "varc"),
                                    new CompStmt(new PrintStmt(new VarExp("varc")),
                                            new CompStmt(new ReadFile(new VarExp("varf"), "varc"),
                                                    new CompStmt(new PrintStmt(new VarExp("varc")),
                                                            new CompStmt(new closeRFile(new VarExp("varf")), new closeRFile(new VarExp("varf")))
                                                    ))))))));}
    private static IStmt relEx(){return new CompStmt(
            new VarDeclStmt("v", new BoolType()),
            new CompStmt(
                    new AssignStmt("v", new RelExp(">", new ValueExp(new IntValue(1)), new ValueExp(new IntValue(0)))),
                    new PrintStmt(new VarExp("v"))
            )
    );}
    private static IStmt newEx(){return new CompStmt(
            new VarDeclStmt("v", new RefType(new IntType())),
            new CompStmt(
                    new NewStmt("v", new ValueExp(new IntValue(20))),
                    new CompStmt(
                            new VarDeclStmt("a", new RefType(new RefType(new IntType()))),
                            new CompStmt(
                                    new NewStmt("a", new VarExp("v")),
                                    new CompStmt(new PrintStmt(new VarExp("v")), new PrintStmt(new VarExp("a")))
                            )
                    )
            )
    );}
    private static IStmt whileEx(){return new CompStmt(
            new VarDeclStmt("v", new IntType()),
            new CompStmt(
                    new AssignStmt("v", new ValueExp(new IntValue(4))),
                    new CompStmt(
                            new WhileStmt(new RelExp(">", new VarExp("v"), new ValueExp(new IntValue(0))), new CompStmt(new PrintStmt(new VarExp("v")), new AssignStmt("v", new ArithExp('-', new VarExp("v"), new ValueExp(new IntValue(1)))))),
                            new PrintStmt(new VarExp("v"))
                    )
            )
    );}
    private static IStmt whilewrongEx(){return new CompStmt(
            new VarDeclStmt("v", new IntType()),
            new CompStmt(
                    new AssignStmt("v", new ValueExp(new IntValue(4))),
                    new CompStmt(
                            new WhileStmt(new ArithExp('-', new VarExp("v"), new ValueExp(new IntValue(3))), new CompStmt(new PrintStmt(new VarExp("v")), new AssignStmt("v", new ArithExp('-', new VarExp("v"), new ValueExp(new IntValue(1)))))),
                            new PrintStmt(new VarExp("v"))
                    )
            )
    );}
    private static IStmt readHeapEx(){return new CompStmt(
            new VarDeclStmt("v", new RefType(new IntType())),
            new CompStmt(
                    new NewStmt("v", new ValueExp(new IntValue(20))),
                    new CompStmt(
                            new VarDeclStmt("a", new RefType(new RefType(new IntType()))),
                            new CompStmt(
                                    new NewStmt("a", new VarExp("v")),
                                    new CompStmt(
                                            new PrintStmt(new ReadHeap(new VarExp("v"))),
                                            new PrintStmt(new ArithExp('+', new ReadHeap(new ReadHeap(new VarExp("a"))), new ValueExp(new IntValue(5))))
                                    )
                            )
                    )
            )
    );}
    private static IStmt writeHeapEx(){return new CompStmt(
            new VarDeclStmt("v", new RefType(new IntType())),
            new CompStmt(
                    new NewStmt("v", new ValueExp(new IntValue(20))),
                    new CompStmt(
                            new PrintStmt(new ReadHeap(new VarExp("v"))),
                            new CompStmt(
                                    new WriteHeap("v", new ValueExp(new IntValue(30))),
                                    new PrintStmt(new ArithExp('+', new ReadHeap(new VarExp("v")), new ValueExp(new IntValue(5))))
                            )

                    )
            )
    );}
    private static IStmt garbageEx(){return new CompStmt(
            new VarDeclStmt("v", new RefType(new IntType())),
            new CompStmt(
                    new NewStmt("v", new ValueExp(new IntValue(20))),
                    new CompStmt(
                            new VarDeclStmt("a", new RefType(new RefType(new IntType()))),
                            new CompStmt(
                                    new NewStmt("a", new VarExp("v")),
                                    new CompStmt(
                                            new NewStmt("v", new ValueExp(new IntValue(30))),
                                            new PrintStmt(new ReadHeap(new ReadHeap(new VarExp("a"))))
                                    )
                            )
                    )
            )
    );}
    private static IStmt garbageEraseEx(){return new CompStmt(
            new VarDeclStmt("v", new RefType(new IntType())),
            new CompStmt(
                    new NewStmt("v", new ValueExp(new IntValue(10))),
                    new CompStmt(
                            new NewStmt("v", new ValueExp(new IntValue(20))),
                            new CompStmt(
                                    new PrintStmt(new ReadHeap(new VarExp("v"))),
                                    new CompStmt(
                                            new VarDeclStmt("a", new RefType(new IntType())),
                                            new CompStmt(
                                                    new NewStmt("a", new ValueExp(new IntValue(30))),
                                                    new CompStmt(
                                                            new NewStmt("a", new ValueExp(new IntValue(40))),
                                                            new PrintStmt(new ReadHeap(new VarExp("a")))

                                                    ))
                                    )
                            )
                    )
            ));}
    private static IStmt forkEx(){return concatStatements(
            new VarDeclStmt("v", new IntType()),
            new VarDeclStmt("a", new RefType(new IntType())),
            new AssignStmt("v", new ValueExp(new IntValue(10))),
            new NewStmt("a", new ValueExp(new IntValue(22))),
            new ForkStmt(
                    concatStatements(
                            new WriteHeap("a", new ValueExp(new IntValue(30))),
                            new AssignStmt("v", new ValueExp(new IntValue(32))),
                            new PrintStmt(new VarExp("v")),
                            new PrintStmt(new ReadHeap(new VarExp("a")))
                    )
            ),
            new PrintStmt(new VarExp("v")),
            new PrintStmt(new ReadHeap(new VarExp("a")))
    );}
    private static IStmt forkforkEx(){return concatStatements(
            new VarDeclStmt("v", new IntType()),
            new VarDeclStmt("a",new RefType(new IntType())),
            new ForkStmt(
                    concatStatements(
                            new AssignStmt("v", new ValueExp(new IntValue(10))),
                            new PrintStmt(new VarExp("v"))
                    )
            ),
            new ForkStmt(
                    concatStatements(
                            new NewStmt("a",new ValueExp(new IntValue(20))),
                            new PrintStmt(new ReadHeap(new VarExp("a")))
                    )
            ),
            new VarDeclStmt("g", new IntType()),
            new VarDeclStmt("h", new IntType()),
            new VarDeclStmt("j", new IntType()),
            new PrintStmt(new ReadHeap(new VarExp("a"))),
            new PrintStmt(new VarExp("v"))
    );}
    private static IStmt forkwrongEx(){return new CompStmt(
            new VarDeclStmt("v", new RefType(new IntType())),
            new CompStmt(
                    new NewStmt("v", new ValueExp(new BoolValue(false))),
                    new CompStmt(
                            new NewStmt("v", new ValueExp(new IntValue(20))),
                            new CompStmt(
                                    new PrintStmt(new ReadHeap(new VarExp("v"))),
                                    new CompStmt(
                                            new VarDeclStmt("a", new RefType(new IntType())),
                                            new CompStmt(
                                                    new NewStmt("a", new ValueExp(new IntValue(30))),
                                                    new CompStmt(
                                                            new NewStmt("a", new ValueExp(new IntValue(40))),
                                                            new PrintStmt(new ReadHeap(new VarExp("a")))

                                                    ))
                                    )
                            )
                    )
            ));}
    public static void main(String[] args) {

        IStmt ex1 = simpleEx();
        IStmt ex2 = arithEx();
        IStmt ex3 = ifEx();
        IStmt ex4 = fileEx();
        IStmt ex5 = relEx();
        IStmt ex6 = newEx();
        IStmt ex7 = whileEx();
        IStmt ex7dot1 = whilewrongEx();
        IStmt ex8 = readHeapEx();
        IStmt ex9 = writeHeapEx();
        IStmt ex10 = garbageEx();
        IStmt ex10dot1 = garbageEraseEx();
        IStmt ex10dot1wrong = forkwrongEx();
        IStmt ex11 = forkEx();
        IStmt ex11dot1 = forkforkEx();

        try{
            MyIDictionary<String, Type> typeEnv = new MyDictionary<>();
            ex10dot1.typecheck(typeEnv);
        }
        catch (MyException e){
            System.out.println(e.getMessage());
            return;
        }

        PrgState prg1 = new PrgState(new MyStack<IStmt>(), new MyDictionary<String, Value>(), new MyList<Value>(), new MyDictionary<StringValue, BufferedReader>(),new MyDictionary<Integer, Value>(), ex1);
        Container repo1 = new Repository(prg1, "log1.txt");
        Controller ctr1 = new Controller(repo1);

        PrgState prg2 = new PrgState(new MyStack<IStmt>(), new MyDictionary<String, Value>(), new MyList<Value>(), new MyDictionary<StringValue, BufferedReader>(),new MyDictionary<Integer, Value>(), ex2);
        Container repo2 = new Repository(prg2,"log2.txt");
        Controller ctr2 = new Controller(repo2);

        PrgState prg3 = new PrgState(new MyStack<IStmt>(), new MyDictionary<String, Value>(), new MyList<Value>(), new MyDictionary<StringValue, BufferedReader>(),new MyDictionary<Integer, Value>(), ex3);
        Container repo3 = new Repository(prg3,"log3.txt");
        Controller ctr3 = new Controller(repo3);

        PrgState prg4 = new PrgState(new MyStack<IStmt>(), new MyDictionary<String, Value>(), new MyList<Value>(), new MyDictionary<StringValue, BufferedReader>(),new MyDictionary<Integer, Value>(), ex4);
        Container repo4 = new Repository(prg4,"log4.txt");
        Controller ctr4 = new Controller(repo4);

        PrgState prg5 = new PrgState(new MyStack<IStmt>(), new MyDictionary<String, Value>(), new MyList<Value>(), new MyDictionary<StringValue, BufferedReader>(),new MyDictionary<Integer, Value>(), ex5);
        Container repo5 = new Repository(prg5,"log5.txt");
        Controller ctr5 = new Controller(repo5);

        PrgState prg6 = new PrgState(new MyStack<IStmt>(), new MyDictionary<String, Value>(), new MyList<Value>(), new MyDictionary<StringValue, BufferedReader>(),new MyDictionary<Integer, Value>(), ex6);
        Container repo6 = new Repository(prg6,"log6.txt");
        Controller ctr6 = new Controller(repo6);

        PrgState prg7 = new PrgState(new MyStack<IStmt>(), new MyDictionary<String, Value>(), new MyList<Value>(), new MyDictionary<StringValue, BufferedReader>(),new MyDictionary<Integer, Value>(), ex7);
        Container repo7 = new Repository(prg7,"log7.txt");
        Controller ctr7 = new Controller(repo7);

        PrgState prg8 = new PrgState(new MyStack<IStmt>(), new MyDictionary<String, Value>(), new MyList<Value>(), new MyDictionary<StringValue, BufferedReader>(),new MyDictionary<Integer, Value>(), ex7dot1);
        Container repo8 = new Repository(prg8,"log8.txt");
        Controller ctr8 = new Controller(repo8);

        PrgState prg9 = new PrgState(new MyStack<IStmt>(), new MyDictionary<String, Value>(), new MyList<Value>(), new MyDictionary<StringValue, BufferedReader>(),new MyDictionary<Integer, Value>(), ex8);
        Container repo9 = new Repository(prg9,"log9.txt");
        Controller ctr9 = new Controller(repo9);

        PrgState prg10 = new PrgState(new MyStack<IStmt>(), new MyDictionary<String, Value>(), new MyList<Value>(), new MyDictionary<StringValue, BufferedReader>(),new MyDictionary<Integer, Value>(), ex9);
        Container repo10 = new Repository(prg10,"log10.txt");
        Controller ctr10 = new Controller(repo10);

        PrgState prg11 = new PrgState(new MyStack<IStmt>(), new MyDictionary<String, Value>(), new MyList<Value>(), new MyDictionary<StringValue, BufferedReader>(),new MyDictionary<Integer, Value>(), ex10);
        Container repo11 = new Repository(prg11,"log11.txt");
        Controller ctr11 = new Controller(repo11);

        PrgState prg12 = new PrgState(new MyStack<IStmt>(), new MyDictionary<String, Value>(), new MyList<Value>(), new MyDictionary<StringValue, BufferedReader>(),new MyDictionary<Integer, Value>(), ex10dot1);
        Container repo12 = new Repository(prg12,"log12.txt");
        Controller ctr12 = new Controller(repo12);

        PrgState prg13 = new PrgState(new MyStack<IStmt>(), new MyDictionary<String, Value>(), new MyList<Value>(), new MyDictionary<StringValue, BufferedReader>(),new MyDictionary<Integer, Value>(), ex10dot1wrong);
        Container repo13 = new Repository(prg13,"log13.txt");
        Controller ctr13 = new Controller(repo13);

        PrgState prg14 = new PrgState(new MyStack<IStmt>(), new MyDictionary<String, Value>(), new MyList<Value>(), new MyDictionary<StringValue, BufferedReader>(),new MyDictionary<Integer, Value>(), ex11);
        Container repo14 = new Repository(prg14,"log14.txt");
        Controller ctr14 = new Controller(repo14);

        PrgState prg15 = new PrgState(new MyStack<IStmt>(), new MyDictionary<String, Value>(), new MyList<Value>(), new MyDictionary<StringValue, BufferedReader>(),new MyDictionary<Integer, Value>(), ex11dot1);
        Container repo15 = new Repository(prg15,"log15.txt");
        Controller ctr15 = new Controller(repo15);

        TextMenu menu = new TextMenu();
        menu.addCommand(new ExitCommand("0", "exit"));
        menu.addCommand(new RunExample("1", ex1.toString(), ctr1));
        menu.addCommand(new RunExample("2",ex2.toString(),ctr2));
        menu.addCommand(new RunExample("3",ex3.toString(),ctr3));
        menu.addCommand(new RunExample("4",ex4.toString(),ctr4));
        menu.addCommand(new RunExample("5",ex5.toString(),ctr5));
        menu.addCommand(new RunExample("6",ex6.toString(),ctr6));
        menu.addCommand(new RunExample("7",ex7.toString(),ctr7));
        menu.addCommand(new RunExample("8",ex7dot1.toString(),ctr8));
        menu.addCommand(new RunExample("9",ex8.toString(),ctr9));
        menu.addCommand(new RunExample("10",ex9.toString(),ctr10));
        menu.addCommand(new RunExample("11",ex10.toString(),ctr11));
        menu.addCommand(new RunExample("12",ex10dot1.toString(),ctr12));
        menu.addCommand(new RunExample("13",ex10dot1wrong.toString(),ctr13));
        menu.addCommand(new RunExample("14",ex11.toString(),ctr14));
        menu.addCommand(new RunExample("15",ex11dot1.toString(),ctr15));
        menu.show();
    }
}
