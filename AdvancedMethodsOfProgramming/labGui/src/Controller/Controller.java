package Controller;

import Model.ADT.MyDictionary;
import Model.ADT.MyHeap;
import Model.ADT.MyIDictionary;
import Model.ADT.MyIStack;
import Model.MyException;
import Model.PrgState;
import Model.Statements.IStmt;
import Model.Values.RefValue;
import Model.Values.Value;
import Repository.*;

import java.util.*;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.stream.Collectors;

public class Controller {
    Container repo;
    ExecutorService executor;

    public Controller(Container repo) {
        this.repo = repo;
    }


    public void runOneStep() {
        this.executor = Executors.newFixedThreadPool(2);
        List<PrgState> states = this.removeCompletedPrg(this.repo.getPrgList());

        if (!states.isEmpty()) {
            Collection<Value> allAddresses = states.stream()
                    .map(PrgState::getSymTable)
                    .map(symTable -> symTable.getDict().values())
                    .reduce(new ArrayList<>(), (acc, values) -> {acc.addAll(values) ; return acc; });

            MyIDictionary heap = states.get(0).getHeap();
            heap.setDict(
                    safeGarbageCollector(
                            addIndirections(
                                    getAddressFromSymbolTable(allAddresses),
                                    heap),
                            heap.getDict()
                    )
            );


            try {
                this.oneStepForAllPrg(states);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }

            executor.shutdownNow();
//            this.repo.setPrgList(this.removeCompletedProgram(states));
        }
    }

    public List<PrgState> removeCompletedPrg(List<PrgState> inPrgList){
        return inPrgList.stream()
                .filter(PrgState::isNotCompleted)
                .collect(Collectors.toList());
    }


    public void oneStepForAllPrg(List<PrgState> states) throws InterruptedException {
        states.forEach(state -> {
            try {
                this.repo.logPrgStateExec(state);
            } catch (MyException ignore) {}
        });

        List<Callable<PrgState>> callableList = states.stream()
                .map(p -> (Callable<PrgState>)(p::oneStep))
                .collect(Collectors.toList());

        List<PrgState> newStates = this.executor.invokeAll(callableList).stream()
                .map(futureObj -> {
                    try { return futureObj.get(); }
                    catch (InterruptedException | ExecutionException ignored) {}
                    return null;
                })
                .filter(Objects::nonNull)
                .collect(Collectors.toList());

        states.addAll(newStates);
        states.forEach(state -> {
            try {
                this.repo.logPrgStateExec(state);
                System.out.println(state);
            }
            catch (MyException ignored) {}
        });
        this.repo.setPrgList(states);
    }


    public void allStep() throws InterruptedException {
        this.executor = Executors.newFixedThreadPool(2);
        List<PrgState> states = this.removeCompletedPrg(this.repo.getPrgList());

        while (!states.isEmpty()) {
            // parse all the states -> symtables -> values -> getAddress? -> combine all the lists into one list
            Collection<Value> allAddresses = states.stream()
                    .map(PrgState::getSymTable)
                    .map(symTable -> symTable.getDict().values())
                    .reduce(new ArrayList<>(), (acc, values) -> {acc.addAll(values) ; return acc; });


            MyIDictionary heap = states.get(0).getHeap();

            heap.setDict(
                    safeGarbageCollector(
                            addIndirections(
                                    getAddressFromSymbolTable(allAddresses),
                                    heap),
                            heap.getDict()
                    )
            );

            this.oneStepForAllPrg(states);
            states = this.removeCompletedPrg(this.repo.getPrgList());
        }
        executor.shutdownNow();
        this.repo.setPrgList(states);
    }

    Map<Integer, Value> safeGarbageCollector(List<Integer> symbolTableAddresses, Map<Integer,Value> heap){
        return heap.entrySet().stream()
                .filter(e->symbolTableAddresses.contains(e.getKey()))
                .collect(Collectors.toMap(Map.Entry::getKey, Map.Entry::getValue));}

    public List<Integer> getAddressFromSymbolTable(Collection<Value> content){
        //will generate a list of values and will filter the reference values and return their addresses
        return content
                .stream()
                .filter(element -> element instanceof RefValue) //check if is RefValue
                .map(element -> ((RefValue) element).getAddress()) //map refvalue to its address
                .collect(Collectors.toList()); //collect in list
    }


    public List<Integer> addIndirections(List<Integer> addressesFromSymbolTable, MyIDictionary heapTable){
        boolean change = true;
        Set<Map.Entry<Integer, Value>> heapSet = heapTable.getEntrySet();//get entry set that needs modifications
        List<Integer> newAddressList = addressesFromSymbolTable.stream().collect(Collectors.toList()); //copy of list in order to add indirections

        //we go through heapSet again and again and each time we add to the address list new indirection level and new addresses which must NOT be deleted
        while (change){
            List<Integer> appendingList = null;
            change = false;
            appendingList = heapSet.stream()
                    .filter(e -> e.getValue() instanceof RefValue)//check if val in heap is RefValue so it can have indirections todo SEMINAR
                    .filter(e -> newAddressList.contains(e.getKey()))//check if address list contains ref to this
                    .map(e -> (((RefValue) e.getValue()).getAddress()))//map the reference to its address so we can add it
                    .filter(e -> !newAddressList.contains(e))//check if the address list already has that reference from prev elems
                    .collect(Collectors.toList());//collect to list

            if(!appendingList.isEmpty()){
                //we still have indirect references so we have to keep checking
                change = true;
                newAddressList.addAll(appendingList);
            }
        }
        return newAddressList;
    }

    public Container getRepo() {
        return repo;
    }
}
