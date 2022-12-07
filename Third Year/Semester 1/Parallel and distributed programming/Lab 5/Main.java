import Algorithms.ParallelClassic;
import Algorithms.ParallelKaratsuba;
import Algorithms.SequentialClassic;
import Algorithms.SequentialKaratsuba;
import Model.AlgorithmChoice;
import Model.MethodChoice;
import Model.Polynomial;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.util.concurrent.ExecutionException;

public class Main {
    private static final MethodChoice METHOD = MethodChoice.PARALLEL;
    private static final AlgorithmChoice ALGORITHM = AlgorithmChoice.KARATSUBA;

    public static void main(String[] args) throws ExecutionException, InterruptedException, IOException {
        Polynomial p1 = new Polynomial(10000);
        System.out.println("p1=" + p1);
        Polynomial p2 = new Polynomial(20000);
        System.out.println("p2=" + p2);
        long startTime = System.nanoTime();
        run(p1, p2);
        long endTime = System.nanoTime();
        double duration = ((double) endTime - (double) startTime) / 1_000_000_000.0;
        BufferedWriter out = new BufferedWriter(
                new FileWriter("results.txt", true));
        out.write(String.format("Duration for %s - degree %s and %s: %s seconds", METHOD + " " + ALGORITHM, p1.getDegree(), p2.getDegree(),duration));
        out.newLine();
        out.close();
        System.out.println("Duration: " + duration + " seconds");
    }

    private static void run(Polynomial p1, Polynomial p2) throws InterruptedException, ExecutionException {
        Polynomial result;
        switch (METHOD) {
            case SEQUENTIAL:
                if (ALGORITHM.equals(AlgorithmChoice.CLASSIC)) {
                    result = SequentialClassic.multiply(p1, p2);
                } else {
                    result = SequentialKaratsuba.multiply(p1, p2);
                }
                break;
            case PARALLEL:
                if (ALGORITHM.equals(AlgorithmChoice.CLASSIC)) {
                    result = ParallelClassic.multiply(p1, p2);
                } else {
                    result = ParallelKaratsuba.multiply(p1, p2, 1);
                }
                break;
            default:
                throw new IllegalStateException("Unexpected value: " + METHOD);
        }
        System.out.println("result=" + result);
    }
}
