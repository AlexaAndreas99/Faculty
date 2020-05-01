package sample;

import Controller.Controller;
import Model.ADT.MyIDictionary;
import Model.ADT.MyIStack;
import Model.MyException;
import Model.PrgState;
import Model.Statements.IStmt;
import Model.Values.Value;
import javafx.beans.property.SimpleObjectProperty;
import javafx.beans.property.SimpleStringProperty;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.Initializable;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;

import java.net.URL;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.ResourceBundle;
import java.util.stream.Collectors;

public class MainWController implements Initializable {
   // public ListView justatest;
    public Controller ctrl;
    private PrgState prg;

    public TableView<Map.Entry<Integer, Value>> HeapT;
    public TableColumn<Map.Entry<Integer, Value>, Integer> HAddress;
    public TableColumn<Map.Entry<Integer, Value>, Value> HValue;

    public TableView<Map.Entry<String, Value>> SymbloTableT;
    public TableColumn<Map.Entry<String, Value>, String> STName;
    public TableColumn<Map.Entry<String, Value>, Value> STValue;

    public ListView OutTableL;
    public ListView FileTableL;
    public ListView PrgStatesL;
    public ListView ExeStackL;

    public TextField NoPrgStates;
    public Button ExeB;

    private void setExeStack() {
        ObservableList stack = FXCollections.observableArrayList();
        stack.add(this.prg.getExeStack().toString());
        this.ExeStackL.setItems(stack);
        ExeStackL.refresh();
    }
    public void setOut() {
        ObservableList out = FXCollections.observableArrayList();
        out.add(this.prg.getOut().toString());
        this.OutTableL.setItems(out);
        OutTableL.refresh();
    }
    public void setFileTable() {
        ObservableList fl = FXCollections.observableArrayList();
        fl.add(this.prg.getFileTable().toString());
        this.FileTableL.setItems(fl);
        FileTableL.refresh();
    }
    private void setPrgStates() {
//        int max=this.ctrl.getRepo().noPrg();
//        this.NoPrgStates.setPromptText(Integer.toString(max));
//
       ObservableList l=FXCollections.observableArrayList();
//        for(int j=0;j<max;j++)
//            l.add(Integer.toString(j));
//        this.PrgStatesL.setItems(l);
        List<String> programIds = ctrl.getRepo().getPrgList().stream().map(p -> p.getId() + "").collect(Collectors.toList());
        this.NoPrgStates.setPromptText(Integer.toString(programIds.size()));
        for(int i=0;i<programIds.size();i++)
            l.add(programIds.get(i));
        this.PrgStatesL.setItems(l);
        this.PrgStatesL.refresh();
    }
    public void setSymTable(){
        ObservableList l=FXCollections.observableArrayList();
        for(Map.Entry<String, Value> entry : this.prg.getSymTable().getAll())
            l.add(entry);
        this.SymbloTableT.setItems(l);
        this.SymbloTableT.refresh();
    }
    public void setHeap(){
        ObservableList l=FXCollections.observableArrayList();
        Iterable<Map.Entry<Integer,Value>> table = this.prg.getHeap().getAll();
        for(Map.Entry<Integer, Value> entry : table)
            l.add(entry);
        this.HeapT.setItems(l);
        this.HeapT.refresh();
    }


    @Override
    public void initialize(URL url, ResourceBundle resourceBundle) {
        this.ctrl=ControllerGUI.ctrl;
        this.prg=this.ctrl.getRepo().getCrtPrg();

        STName.setCellValueFactory(p -> new SimpleStringProperty(p.getValue().getKey() + ""));
        STValue.setCellValueFactory(p -> new SimpleObjectProperty<>(p.getValue().getValue()));

        HAddress.setCellValueFactory(p -> new SimpleObjectProperty<>(p.getValue().getKey()));
        HValue.setCellValueFactory(p -> new SimpleObjectProperty<>(p.getValue().getValue()));
        PrgStatesL.setOnMouseClicked(actionEvent -> populate());
        //PrgStatesL.getProperties().put("selectFirstRowByDefault", true);
       //this.populate();
        setPrgStates();
        setExeStack();
        if (!PrgStatesL.getItems().isEmpty())
            PrgStatesL.getSelectionModel().select(0);


    }

    private PrgState getCurrentProgramState() {
        if (this.PrgStatesL.getSelectionModel().getSelectedIndex() == -1)
            return null;

        String currentId = (String) PrgStatesL.getSelectionModel().getSelectedItem();
        return this.ctrl.getRepo().getProgramStateWithId(Integer.valueOf(currentId));
    }
    public void executeOneStep() throws InterruptedException {
        int selectedId = Integer.parseInt((String)PrgStatesL.getSelectionModel().getSelectedItem());
        System.out.println(selectedId);
        System.out.println(ctrl.getRepo().getPrgList().get(0).getId());
        PrgState selectedProgramState = null;
        for (PrgState ps : ctrl.getRepo().getPrgList())
            if (ps.getId() == selectedId) {
                System.out.println(ps.getId());
                System.out.println(selectedId);
                selectedProgramState = ps;
                break;
            }
        if (selectedProgramState == null || selectedProgramState.getExeStack().isEmpty()) {
            Alert alert = new Alert(Alert.AlertType.ERROR, "Empty Execution Stack");
            alert.showAndWait();
            return ;
        }

        ctrl.runOneStep();


        populate();
        //setSymTable();
//        setExeStack();
//        setFileTable();
//        setHeap();
//        setOut();
//        setPrgStates();


    }
    private void populate() {
        setPrgStates();

        int psId = Integer.parseInt((String)PrgStatesL.getSelectionModel().getSelectedItem());

        if (ctrl.getRepo().getPrgList().isEmpty()) {
            SymbloTableT.setItems(FXCollections.observableList(new ArrayList<>()));
            SymbloTableT.refresh();
            return;
        }
        PrgState currentProgramState = null;
        for (PrgState ps : ctrl.getRepo().getPrgList())
            if (ps.getId() == psId) {
                currentProgramState = ps;
                break;
            }
        if (currentProgramState == null) {
            ExeStackL.setItems(FXCollections.observableList(new ArrayList<>()));
            ExeStackL.refresh();
            return;
        }
        this.prg=currentProgramState;
        setExeStack();
        setSymTable();
        setHeap();
        setFileTable();
        setOut();

    }
}
