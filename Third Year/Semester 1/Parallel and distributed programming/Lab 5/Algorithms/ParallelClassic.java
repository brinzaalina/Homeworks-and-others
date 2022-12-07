package Algorithms;

import Model.Polynomial;
import Model.Task;

import java.util.List;
import java.util.concurrent.Executors;
import java.util.concurrent.ThreadPoolExecutor;
import java.util.concurrent.TimeUnit;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

public class ParallelClassic {
    private static final int NR_THREADS = 4;

    public static Polynomial multiply(Polynomial p1, Polynomial p2) throws InterruptedException {
        int sizeOfResultCoefficientList = p1.getDegree() + p2.getDegree() + 1;
        List<Integer> coefficients = IntStream.range(0, sizeOfResultCoefficientList)
                .mapToObj(i -> 0)
                .collect(Collectors.toList());
        Polynomial result = new Polynomial(coefficients);

        ThreadPoolExecutor executor = (ThreadPoolExecutor) Executors.newFixedThreadPool(NR_THREADS);
        int nrOfTasks = sizeOfResultCoefficientList / NR_THREADS;
        if (nrOfTasks == 0) {
            nrOfTasks = 1;
        }

        int end;
        for (int i = 0; i < sizeOfResultCoefficientList; i += nrOfTasks) {
            end = i + nrOfTasks;
            Task task = new Task(i, end, p1, p2, result);
            executor.execute(task);
        }

        executor.shutdown();
        executor.awaitTermination(50, TimeUnit.SECONDS);

        return result;
    }
}
