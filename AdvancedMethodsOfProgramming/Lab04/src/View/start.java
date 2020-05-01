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
        IStmt ex1 = new CompStmt(new VarDeclStmt("v", new IntType()), new CompStmt(new AssignStmt("v", new ValueExp(new IntValue(2))), new PrintStmt(new VarExp("v"))));

        IStmt ex2 = new CompStmt(new VarDeclStmt("a", new IntType()), new CompStmt(new VarDeclStmt("b", new IntType()),
                new CompStmt(new AssignStmt("a", new ArithExp('+', new ValueExp(new IntValue(2)), new
                        ArithExp('*', new ValueExp(new IntValue(3)), new ValueExp(new IntValue(5))))),
                        new CompStmt(new AssignStmt("b", new ArithExp('+', new VarExp("a"), new
                                ValueExp(new IntValue(1)))), new PrintStmt(new VarExp("b"))))));

        IStmt ex3 = new CompStmt(new VarDeclStmt("a", new BoolType()),
                new CompStmt(new VarDeclStmt("v", new IntType()),
                        new CompStmt(new AssignStmt("a", new ValueExp(new BoolValue(true))),
                                new CompStmt(new IfStmt(new VarExp("a"), new AssignStmt("v", new ValueExp(new
                                        IntValue(2))), new AssignStmt("v", new ValueExp(new IntValue(3)))), new PrintStmt(new
                                        VarExp("v"))))));
        IStmt ex4 = new CompStmt(new VarDeclStmt("varf", new StringType()), new CompStmt(new AssignStmt("varf", new ValueExp(new StringValue("./src/Repository/test.in"))),
                new CompStmt(new OpenRFile(new VarExp("varf")),
                        new CompStmt(new VarDeclStmt("varc", new IntType()),
                                new CompStmt(new ReadFile(new VarExp("varf"), "varc"),
                                        new CompStmt(new PrintStmt(new VarExp("varc")),
                                                new CompStmt(new ReadFile(new VarExp("varf"), "varc"),
                                                        new CompStmt(new PrintStmt(new VarExp("varc")),
                                                                new CompStmt(new closeRFile(new VarExp("varf")), new closeRFile(new VarExp("varf")))
                                                        ))))))));

        IStmt ex5 = new CompStmt(
                new VarDeclStmt("v", new BoolType()),
                new CompStmt(
                        new AssignStmt("v", new RelExp(">", new ValueExp(new IntValue(1)), new ValueExp(new IntValue(0)))),
                        new PrintStmt(new VarExp("v"))
                )
        );

        IStmt ex6 = new CompStmt(
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
        );
        IStmt ex7 = new CompStmt(
                new VarDeclStmt("v", new IntType()),
                new CompStmt(
                        new AssignStmt("v", new ValueExp(new IntValue(4))),
                        new CompStmt(
                                new WhileStmt(new RelExp(">", new VarExp("v"), new ValueExp(new IntValue(0))), new CompStmt(new PrintStmt(new VarExp("v")), new AssignStmt("v", new ArithExp('-', new VarExp("v"), new ValueExp(new IntValue(1)))))),
                                new PrintStmt(new VarExp("v"))
                        )
                )
        );

        IStmt ex7dot1 = new CompStmt(
                new VarDeclStmt("v", new IntType()),
                new CompStmt(
                        new AssignStmt("v", new ValueExp(new IntValue(4))),
                        new CompStmt(
                                new WhileStmt(new ArithExp('-', new VarExp("v"), new ValueExp(new IntValue(3))), new CompStmt(new PrintStmt(new VarExp("v")), new AssignStmt("v", new ArithExp('-', new VarExp("v"), new ValueExp(new IntValue(1)))))),
                                new PrintStmt(new VarExp("v"))
                        )
                )
        );

        IStmt ex8 = new CompStmt(
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
        );
        IStmt ex9 = new CompStmt(
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
        );

        IStmt ex10 = new CompStmt(
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
        );


        IStmt ex10dot1 = new CompStmt(
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
                ));

        IStmt ex10dot1wrong = new CompStmt(
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
                ));

        IStmt ex11 = concatStatements(
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
        );
        IStmt ex11dot1=concatStatements(
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
        );
        // int v; Ref int a; fork(v=10; print(v)); fork(new(a, 20); print(Rh(a))); print(v); print(Rh(a));

        //System.out.println(ex11.toString());

        MyIStack<IStmt> stack = new MyStack<IStmt>();
        MyIDictionary<String, Value> symTable = new MyDictionary<String, Value>();
        MyIList<Value> out = new MyList<Value>();
        MyIDictionary<StringValue, BufferedReader> FileTable = new MyDictionary<StringValue, BufferedReader>();
        MyIDictionary<Integer, Value> heap = new MyDictionary<>();
        PrgState state = new PrgState(stack, symTable, out, FileTable, heap, ex10dot1);
        Container repo = new Repository(state, "./src/Repository/logFile.txt");
        Controller ctrl = new Controller(repo);

        System.out.println(ex10dot1.toString());
        try{
            MyIDictionary<String, Type> typeEnv = new MyDictionary<>();
            ex10dot1.typecheck(typeEnv);
        }
        catch (MyException e){
            System.out.println(e.getMessage());
        return;
        }

        try {
            ctrl.allStep();
            System.out.println(out.toString());
        } catch (InterruptedException e) {
            System.out.println(e.getMessage());
        }
    }
}