public class ColumnThread implements Runnable {
    private final Integer[][] result;
    private final Integer left;
    private final Integer right;

    public ColumnThread(Integer[][] result, Integer left, Integer right) {
        this.result = result;
        this.left = left;
        this.right = right;
    }

    @Override
    public void run() {
        int n = Main.a;
        int m = Main.c;
        int i = left % n;
        int j = left / n;
        int k = right - left;
        for (int index = 0; index < k; index++) {
            result[i][j] = Matrix.getCell(Main.matrix1, Main.matrix2, i, j);
            i++;
            if (i == n) {
                i = 0;
                j++;
            }
        }
    }
}
