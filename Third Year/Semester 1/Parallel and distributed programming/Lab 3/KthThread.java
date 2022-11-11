public class KthThread implements Runnable {
    private final Integer[][] result;
    private final Integer k;
    private final Integer stepSize;

    public KthThread(Integer[][] result, Integer k, Integer stepSize) {
        this.result = result;
        this.k = k;
        this.stepSize = stepSize;
    }

    @Override
    public void run() {
        int n = Main.a;
        int m = Main.c;
        int i = 0;
        int j = k;
        while (true) {
            int overshoot = j / m;
            i += overshoot;
            j -= overshoot * m;
            if (i >= n) {
                break;
            }
            result[i][j] = Matrix.getCell(Main.matrix1, Main.matrix2, i, j);
            j += stepSize;
        }
    }
}
