import java.util.*;

public class Graph {
    /*
    nodesNumber : int representing the number of nodes in the graph;
    nodes: map with (key, value) pairs; key is the number of the node, value is a set of neighbour nodes;
     */
    private int nodesNumber;
    private Map<Integer, Set<Integer>> nodes ;

    //constructor
    public Graph( int n){
        this.nodesNumber = n;

        nodes = new HashMap<>();
        for(int node=0; node< n; node++){
            nodes.put(node, new HashSet<>());
        }
    }

    //add a new edge to the graph
    public boolean addEdge(int startNode, int endNode){
        return nodes.get(startNode).add(endNode);
    }

    //checks if there is an edge between startNode and endNode
    public boolean existsEdge(int startNode, int endNode){
        return nodes.get(startNode).contains(endNode);
    }

    public int getNodesNumber() { return nodesNumber; }

    public void setNodesNumber(int nodesNumber) { this.nodesNumber = nodesNumber; }

    public Map<Integer, Set<Integer>> getNodes() { return nodes; }

    public void setNodes(Map<Integer, Set<Integer>> nodes) { this.nodes = nodes; }

    // generate a random graph of a given number of nodes
    public static Graph generateRandomGraph(int nodesNumber){
        Graph graph = new Graph(nodesNumber);
        for(int i=0; i< nodesNumber; i++){
            for(int j=0; j< nodesNumber; j++){
                if(i!=j){
                    if(Math.random() < 0.5 && !graph.existsEdge(i,j)){
                        graph.addEdge(i,j);
                    }
                }
            }
        }
        return graph;
    }

    @Override
    public String toString() {
        return "Graph{" +
                "nodesNumber=" + nodesNumber +
                ", nodes=" + nodes +
                '}';
    }
}
