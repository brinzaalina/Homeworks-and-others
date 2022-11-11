import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;
import java.util.concurrent.Executors;
import java.util.concurrent.ThreadPoolExecutor;
import java.util.concurrent.TimeUnit;

public class Main {
    public static Integer a, b, c;
    public static Integer functionType;
    public static Integer scanType;
    public static Integer taskNumber;
    public static Matrix matrix1;
    public static Matrix matrix2;

    public static void getParams() {
        Scanner scanner = new Scanner(System.in);
        System.out.println("a: ");
        a = scanner.nextInt();
        System.out.println("b: ");
        b = scanner.nextInt();
        System.out.println("c: ");
        c = scanner.nextInt();
        System.out.println("function type:");
        System.out.println("0. Task");
        System.out.println("1. Pool");
        functionType = scanner.nextInt();
        System.out.println("scan type:");
        System.out.println("0. row");
        System.out.println("1. column");
        System.out.println("2. kth");
        scanType = scanner.nextInt();
        System.out.println("Enter the number of the tasks:");
        taskNumber = scanner.nextInt();
        generateMatrix();
    }

    public static void generateMatrix() {
        matrix1 = new Matrix(a, b);
        matrix2 = new Matrix(b, c);
    }

    public static void hardCodeParams() {
        a = 3;
        b = 2;
        c = 2;
        functionType = 0;
        scanType = 0;
        matrix1 = new Matrix(new Integer[][]{{1, 2}, {3, 4}, {5, 6}});
        matrix2 = new Matrix(new Integer[][]{{7, 8}, {9, 10}});
        taskNumber = 3;
    }

    public static Matrix productByTasks() throws InterruptedException {
        Integer[][] result = new Integer[a][c];
        List<Thread> threads = new ArrayList<>();
        int iterations = a * c / taskNumber;
        for (int i = 0; i < taskNumber; i++) {
            int left = i * iterations;
            int right = Math.min((i + 1) * iterations, a * c);
            if (functionType == 0) {
                threads.add(new Thread(new RowThread(result, left, right)));
            } else if (functionType == 1) {
                threads.add(new Thread(new ColumnThread(result, left, right)));
            } else {
                threads.add(new Thread(new KthThread(result, i, taskNumber)));
            }
        }
        for (Thread thread : threads) {
            thread.start();
        }
        for (Thread thread : threads) {
            thread.join();
        }
        return new Matrix(result);
    }

    public static Matrix productByThreadPool() throws InterruptedException {
        ThreadPoolExecutor executor = (ThreadPoolExecutor) Executors.newFixedThreadPool(taskNumber);
        Integer[][] result = new Integer[a][c];
        List<Runnable> tasks = new ArrayList<>();
        int iterations = a * c / taskNumber;
        for (int i = 0; i < taskNumber; i++) {
            int left = i * iterations;
            int right = Math.min((i + 1) * iterations, a * c);
            if (functionType == 0) {
                tasks.add(new RowThread(result, left, right));
            } else if (functionType == 1) {
                tasks.add(new ColumnThread(result, left, right));
            } else {
                tasks.add(new KthThread(result, i, taskNumber));
            }
        }
        for (Runnable task : tasks) {
            executor.execute(task);
        }
        executor.shutdown();
        while (!executor.awaitTermination(1, TimeUnit.DAYS)) {
            System.out.println("Not yet. Still waiting for termination");
        }
        return new Matrix(result);
    }

    public static void main(String[] args) throws InterruptedException {
        while (true) {
            getParams();
//        hardCodeParams();
            Matrix trueProduct = Matrix.getProduct(matrix1, matrix2);
            Matrix computedProduct;
            double startTime = System.nanoTime();
            if (functionType == 0) {
                computedProduct = productByTasks();
            } else {
                computedProduct = productByThreadPool();
            }
            double endTime = System.nanoTime();
            System.out.println("Elapsed time: " + (endTime - startTime) / 1_000_000_000.0);
            if (trueProduct.equals(computedProduct)) {
                System.out.println("Correct");
            } else {
                System.out.println("Incorrect");
            }
        }
    }
}
