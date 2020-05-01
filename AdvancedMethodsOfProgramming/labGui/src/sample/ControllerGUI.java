package sample;

import Controller.Controller;
import Model.ADT.MyDictionary;
import Model.ADT.MyList;
import Model.ADT.MyStack;
import Model.Expressions.*;
import Model.PrgState;
import Model.Statements.*;
import Model.Types.BoolType;
import Model.Types.IntType;
import Model.Types.RefType;
import Model.Types.StringType;
import Model.Values.BoolValue;
import Model.Values.IntValue;
import Model.Values.StringValue;
import Model.Values.Value;
import Repository.Container;
import Repository.Repository;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.ListView;
import javafx.stage.Modality;
import javafx.stage.Stage;

import java.io.BufferedReader;
import java.io.IOException;
import java.net.URL;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;
import java.util.ResourceBundle;

public class ControllerGUI implements Initializable {
    public ListView list;
    public Button ASD;
    public MainWController mainCtrl;
    public static Controller ctrl;

    private IStmt getProgram(int k)
    {
        if(k==0)
            return simpleEx();
        if(k==1)
            return arithEx();
        if(k==2)
            return ifEx();
        if(k==3)
            return fileEx();
        if(k==4)
            return relEx();
        if(k==5)
            return newEx();
        if(k==6)
            return whileEx();
        if(k==7)
            return readHeapEx();
        if(k==8)
            return writeHeapEx();
        if(k==9)
            return garbageEx();
        if(k==10)
            return garbageEraseEx();
        if(k==11)
            return forkEx();
        if(k==12)
            return forkforkEx();
        if(k==13)
            return switchEx();

        return simpleEx();
    }
    public void populate(){
        IStmt ex1 = simpleEx();
        IStmt ex2 = arithEx();
        IStmt ex3 = ifEx();
        IStmt ex4 = fileEx();
        IStmt ex5 = relEx();
        IStmt ex6 = newEx();
        IStmt ex7 = whileEx();
        //IStmt ex7dot1 = whilewrongEx();
        IStmt ex8 = readHeapEx();
        IStmt ex9 = writeHeapEx();
        IStmt ex10 = garbageEx();
        IStmt ex10dot1 = garbageEraseEx();
        //IStmt ex10dot1wrong = forkwrongEx();
        IStmt ex11 = forkEx();
        IStmt ex11dot1 = forkforkEx();
        IStmt ex12=switchEx();
        ObservableList l=FXCollections.observableArrayList();
        l.addAll(ex1.toString(),ex2.toString(),ex3.toString(),ex4.toString(),ex5.toString(),ex6.toString(),ex7.toString()
                ,ex8.toString(),ex9.toString(),ex10.toString(),ex10dot1.toString(),ex11.toString()
                ,ex11dot1.toString(),ex12.toString());
        list.setItems(l);
    }

    @Override
    public void initialize(URL url, ResourceBundle resourceBundle) {
        populate();
    }

    public void open(ActionEvent actionEvent) throws IOException {
        Integer k=this.list.getSelectionModel().getSelectedIndex();
        IStmt ex1 = getProgram(k);
        PrgState prg1 = new PrgState(new MyStack<IStmt>(), new MyDictionary<String, Value>(), new MyList<Value>(), new MyDictionary<StringValue, BufferedReader>(),new MyDictionary<Integer, Value>(), ex1);
        Container repo1 = new Repository(prg1, "log1.txt");
        Controller ctr1 = new Controller(repo1);
       this.ctrl=ctr1;

        FXMLLoader fxmlLoader=new FXMLLoader(getClass().getResource("MainW.fxml"));
        Parent root1 = (Parent) fxmlLoader.load();
        Stage stage = new Stage();
        stage.setScene(new Scene(root1));
        stage.initModality(Modality.APPLICATION_MODAL);
        stage.show();
    }
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
                            new AssignStmt("v", new ValueExp(new IntValue(32))),
                            new PrintStmt(new VarExp("v")),
                            new PrintStmt(new ReadHeap(new VarExp("a")))
                    )
            ),
            new VarDeclStmt("q",new BoolType()),
            new AssignStmt("q",new ValueExp(new BoolValue(true))),
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
    private static IStmt switchEx(){
        return concatStatements(
                new VarDeclStmt("a",new IntType()),
                new VarDeclStmt("b",new IntType()),
                new VarDeclStmt("c",new IntType()),
                new AssignStmt("a",new ValueExp(new IntValue(1))),
                new AssignStmt("b",new ValueExp(new IntValue(2))),
                new AssignStmt("c",new ValueExp(new IntValue(5))),
                new SwitchStmt(new CompStmt(new PrintStmt(new VarExp("a")),new PrintStmt(new VarExp("b"))),
                        new CompStmt(new PrintStmt(new ValueExp(new IntValue(100))),new PrintStmt(new ValueExp(new IntValue(200)))),
                        new PrintStmt(new ValueExp(new IntValue(300))),
                        new ArithExp('*',new ValueExp(new IntValue(10)),new VarExp("a")),
                        new ArithExp('*',new VarExp("b"),new VarExp("c")),
                        new ValueExp(new IntValue(10))
                ),
                new PrintStmt(new ValueExp(new IntValue(300)))
        );
    }
}
