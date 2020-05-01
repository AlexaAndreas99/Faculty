package Model;

import Model.ADT.MyIDictionary;
import Model.ADT.MyIHeap;
import Model.ADT.MyIList;
import Model.ADT.MyIStack;
import Model.Statements.IStmt;
import Model.Values.StringValue;
import Model.Values.Value;

import java.io.BufferedReader;

public class PrgState {

    private MyIStack<IStmt> exeStack;
    private MyIDictionary<String, Value> symTable;
    private MyIList<Value> out;
    private MyIDictionary<StringValue, BufferedReader> FileTable;
    private MyIDictionary<Integer, Value> heap;
    private static int lastid = 0;
    private int id;


    public PrgState oneStep() throws MyException {
        MyIStack<IStmt> stk = this.getExeStack();
        if (stk.size() == 0) {
            throw new MyException("prgstate stack is empty");
        }
        IStmt crtStmt = stk.pop();
        return crtStmt.execute(this);
    }

    public MyIDictionary<Integer, Value> getHeap() {
        return heap;
    }

    public void setHeap(MyIDictionary heap) {
        this.heap = heap;
    }

    private IStmt st;

    public MyIDictionary<StringValue, BufferedReader> getFileTable() {
        return FileTable;
    }

    public void setFileTable(MyIDictionary<StringValue, BufferedReader> fileTable) {
        FileTable = fileTable;
    }

    public Boolean isNotCompleted() {
        return this.exeStack.size() != 0;
    }

    public PrgState(MyIStack<IStmt> stk, MyIDictionary<String, Value> symtbl, MyIList<Value> ot, MyIDictionary<StringValue, BufferedReader> ft, MyIDictionary<Integer, Value> heap, IStmt s) {
        this.exeStack = stk;
        this.symTable = symtbl;
        this.out = ot;
        this.FileTable = ft;
        this.heap = heap;
        st = s;
        exeStack.push(s);
        this.id = 0;
    }

    public synchronized void setNewId() {
        lastid++;
        this.id = lastid;
    }

    @Override
    public String toString() {
        return "[" + this.id + "]" + exeStack.toString() + "\n"
                + "[" + this.id + "]" + symTable.toString() + "\n"
                + "[" + this.id + "]" + out.toString() + "\n"
                + "[" + this.id + "]" + this.FileTable.toString() + '\n'
                + "[" + this.id + "]" + this.heap.toString() + '\n';
    }

    public MyIStack<IStmt> getExeStack() {
        return exeStack;
    }

    public IStmt getSt() {
        return st;
    }

    public void setExeStack(MyIStack<IStmt> exeStack) {
        this.exeStack = exeStack;
    }

    public MyIDictionary<String, Value> getSymTable() {
        return symTable;
    }

    public int getId() {
        return id;
    }

    public void setSymTable(MyIDictionary<String, Value> symTable) {
        this.symTable = symTable;
    }

    public MyIList<Value> getOut() {
        return out;
    }

    public void setOut(MyIList<Value> out) {
        this.out = out;
    }

}
