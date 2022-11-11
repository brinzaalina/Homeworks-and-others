public class RowThread implements Runnable {
    private final Integer[][] result;
    private final Integer left;
    private final Integer right;

    public RowThread(Integer[][] result, Integer left, Integer right) {
        this.result = result;
        this.left = left;
        this.right = right;
    }

    @Override
    public void run() {
        int n = Main.a;
        int m = Main.c;
        int i = left / m;
        int j = left % m;
        int k = right - left;
        for (int index = 0; index < k; index++) {
            result[i][j] = Matrix.getCell(Main.matrix1, Main.matrix2, i, j);
            j++;
            if (j == m) {
                j = 0;
                i++;
            }
        }
    }
}
