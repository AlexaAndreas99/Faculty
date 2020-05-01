package Repository;

import Model.MyException;
import Model.PrgState;

import java.io.*;
import java.util.ArrayList;
import java.util.List;

public class Repository implements Container {
    List<PrgState> programStates;
    String logFilePath;

    public Repository(PrgState programStates, String logFilePath) {
        this.programStates=new ArrayList<PrgState>();
        this.programStates.add(programStates);
        this.logFilePath = logFilePath;
    }

    @Override
    public List<PrgState> setPrgList(List<PrgState> PrgList) {
        return this.programStates=PrgList;
    }

    @Override
    public List<PrgState> getPrgList() {
        return this.programStates;
    }

    @Override
    public void logPrgStateExec(PrgState ps) throws MyException {
    try (PrintWriter logFile=new PrintWriter(new BufferedWriter(new FileWriter(this.logFilePath,true)))){
        logFile.println(ps.toString()+'\n');
    }
    catch (IOException ioe){
        throw new MyException(ioe.getMessage());
        }
    }

    @Override
    public PrgState getCrtPrg() {
        return this.programStates.get(0);
    }
}
