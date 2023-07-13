import mpi.MPI;

import java.util.Arrays;
import java.util.Map;

public class GraphColoring {
    public static Map<Integer,String> graphColoringMain(int mpiSize, Graph graph, Colors colors) throws Exception {

        int colorsNumber = colors.getColorsNumber();
        int[] codes = graphColoringRecursive(0,graph,colorsNumber, new int[graph.getNodesNumber()], 0, mpiSize, 0);

        //no solution
        if (codes[0] == -1){
            throw new Exception("No solution found!");
        }

        return colors.getColorsForCodes(codes);
    }
    private static int[] graphColoringRecursive(int nodeId, Graph graph, int colorsNumber, int[] codes, int mpiRank, int mpiSize, int power){
        int nodesNumber = graph.getNodesNumber();

        //invalid solution
        if(!isColorValid(nodeId,codes, graph)){
            return fillArray(nodesNumber, -1);
        }

        //valid solution
        if(nodeId + 1 == graph.getNodesNumber()){
            return codes;
        }

        //valid destination processes
        int coefficient = (int) Math.pow(colorsNumber,power);
        int colorCode = 0;
        int destination = mpiRank + coefficient * (colorCode + 1);

        while (colorCode + 1 < colorsNumber && destination < mpiSize){
            colorCode++;
            destination = mpiRank+coefficient*(colorCode + 1 );
        }

        //send data to destination process
        int nextNode = nodeId +1;
        int nextPower = power + 1;

        for (int currentColorCode = 1; currentColorCode < colorCode; currentColorCode++){
            destination = mpiRank + coefficient * currentColorCode;

            int[] data = new int[]{mpiRank, nextNode, nextPower};
            MPI.COMM_WORLD.Send(data,0,data.length,MPI.INT,destination,0);

            int[] nextColorCodes = Arrays.copyOf(codes,codes.length);
            nextColorCodes[nextNode] = currentColorCode;

            MPI.COMM_WORLD.Send(nextColorCodes, 0, nodesNumber, MPI.INT, destination, 0);
        }

        //try color 0 for next node on this process
        int[] nextColorCodes = Arrays.copyOf(codes,codes.length);
        nextColorCodes[nextNode] = 0;

        int[] result = graphColoringRecursive(nextNode, graph, colorsNumber, nextColorCodes, mpiRank, mpiSize, nextPower);
        if(result[0] != -1){
            return result;
        }

        //receive data from destination processes
        for (int currentColorCode = 1; currentColorCode < colorCode; currentColorCode++){
            destination = mpiRank + coefficient * currentColorCode;
            result = new int[nodesNumber];

            MPI.COMM_WORLD.Recv(result,0,nodesNumber,MPI.INT,destination,MPI.ANY_TAG);
            if(result[0] != -1){
                return result;
            }
        }

        //try remaining colors for next node (on this process)
        for (int currentColorCode = colorCode ; currentColorCode < colorsNumber; currentColorCode++){
            nextColorCodes = Arrays.copyOf(codes,codes.length);
            nextColorCodes[nextNode] = currentColorCode;

            result = graphColoringRecursive(nextNode, graph, colorsNumber, nextColorCodes, mpiRank, mpiSize, nextPower);

            if(result[0] != -1){
                return result;
            }
        }

        //invalid solution (result is an array of -1)
        return result;

    }

    public static void graphColoringChild(int mpiRank, int mpiSize, Graph graph, int colorsNumber) {
        int nodesNumber = graph.getNodesNumber();

        //receive data
        int[] data = new int[3];
        MPI.COMM_WORLD.Recv(data, 0, data.length, MPI.INT, MPI.ANY_SOURCE, MPI.ANY_TAG);

        int parent = data[0];
        int nodeId = data[1];
        int power = data[2];

        int[] codes = new int[nodesNumber];
        MPI.COMM_WORLD.Recv(codes, 0, nodesNumber, MPI.INT, MPI.ANY_SOURCE, MPI.ANY_TAG);

        //recursive call
        int[] result = graphColoringRecursive(nodeId, graph, colorsNumber, codes, mpiRank, mpiSize, power);

        //send data to parent
        MPI.COMM_WORLD.Send(result, 0, nodesNumber, MPI.INT, parent, 0);

    }

    //fill an array of a given size with a given value
    private static int[] fillArray(int length, int value) {
        int[] array = new int[length];
        Arrays.fill(array, value);

        return array;
    }


    //verify if two neighbors have the same color
    private static boolean isColorValid( int node, int[] codes, Graph graph){
        for(int current=0; current < node; current++){
            if((graph.existsEdge(node,current) || graph.existsEdge(current,node)) && codes[node] == codes[current]){
                return false;
            }
        }
        return true;
    }
}
