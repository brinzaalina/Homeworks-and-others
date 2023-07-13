import java.util.*;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class GraphColoring {
    public static Map<Integer,String> getColoredGraph (int threadsNumber, Graph graph, Colors colors) throws Exception{
        Vector<Integer> codes = new Vector<>();

        int codesNumber = colors.getColorsNumber();
        Vector<Integer> partialCodes = new Vector<>(Collections.nCopies(graph.getNodesNumber(),0));
        Lock lock = new ReentrantLock();

        getColoredGraphRecursive(new AtomicInteger(threadsNumber), 0, graph, codesNumber, partialCodes, lock, codes );

        //no solution
        if(codes.isEmpty()){
            throw new Exception("No solution found!");
        }

        //solution found
        return colors.getColorsForCodes(codes);
    }

    private static void getColoredGraphRecursive(AtomicInteger threadsNumber, int nodeId, Graph graph, int codesNumber, Vector<Integer> partialCodes, Lock lock, Vector<Integer>codes){
        //solution already found
        if(!codes.isEmpty()){
            return;
        }

        //solution
        if(nodeId+1 == graph.getNodesNumber()){
            if(isColorValid(nodeId, partialCodes, graph)){
                lock.lock();
                if(codes.isEmpty()){
                    codes.addAll(partialCodes);
                }
                lock.unlock();
            }
            return;
        }

        //find possible colors for the next node
        int nextNode = nodeId + 1;

        List<Thread> threads = new ArrayList<>();
        List<Integer> validColors = new ArrayList<>();

        for(int code = 0; code < codesNumber; code++){
            partialCodes.set(nextNode, code);
            if(isColorValid(nextNode, partialCodes, graph)){
                if (threadsNumber.getAndDecrement() > 0 ){
                    Vector<Integer> nextPartialCodes = new Vector<>(partialCodes);

                    Thread thread = new Thread(()-> getColoredGraphRecursive(threadsNumber, nextNode, graph, codesNumber, nextPartialCodes, lock, codes));
                    thread.start();
                    threads.add(thread);
                }
                else {
                    validColors.add(code);
                }
            }
        }

        //join threads
        for (Thread thread : threads){
            try {
                thread.join();
            }
            catch (InterruptedException e){
                e.printStackTrace();
            }
        }

        for (int code : validColors){
            partialCodes.set(nextNode, code);
            Vector<Integer> nextPartialCodes = new Vector<>(partialCodes);
            getColoredGraphRecursive(threadsNumber, nextNode, graph, codesNumber, nextPartialCodes, lock, codes);
        }

    }

    //verify if two neighbors have the same
    private static boolean isColorValid( int node, Vector<Integer> codes, Graph graph){
        for(int current=0; current < node; current++){
            if((graph.existsEdge(node,current) || graph.existsEdge(current,node)) && codes.get(node) == codes.get(current).intValue()){
                return false;
            }
        }
        return true;
    }
}
