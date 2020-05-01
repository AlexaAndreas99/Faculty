package Repository;

import Model.MyException;
import Model.PrgState;

import java.util.List;

public interface Container {

    PrgState getCrtPrg();
    void logPrgStateExec(PrgState ps)throws MyException;
    List<PrgState> getPrgList();
    List<PrgState> setPrgList(List<PrgState> PrgList);
}
