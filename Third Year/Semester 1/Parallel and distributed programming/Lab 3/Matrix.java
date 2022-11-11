import java.util.Random;

public class Matrix {
    private final Integer[][] matrix;
    private final Integer n, m;

    public Matrix(Integer[][] matrix) {
        this.matrix = matrix;
        this.n = matrix.length;
        this.m = matrix[0].length;
    }

    public Matrix(int n, int m) {
        this.matrix = new Integer[n][m];
        this.n = n;
        this.m = m;
        Random random = new Random();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                this.matrix[i][j] = random.nextInt(10);
            }
        }
    }

    public static int getCell(Matrix a, Matrix b, int i, int j) {
        int result = 0;
        for (int k = 0; k < a.m; k++) {
            result += a.get(i, k) * b.get(k, j);
        }
        return result;
    }

    public int get(int i, int j) {
        return matrix[i][j];
    }

    public static Matrix getProduct(Matrix a, Matrix b) {
        Integer[][] result = new Integer[a.n][b.m];
        for (int i = 0; i < a.n; i++) {
            for (int j = 0; j < b.m; j++) {
                result[i][j] = getCell(a, b, i, j);
            }
        }
        return new Matrix(result);
    }

    public void print() {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                System.out.print(matrix[i][j] + " ");
            }
            System.out.println();
        }
        System.out.println();
    }

    @Override
    public boolean equals(Object obj) {
        if (!(obj instanceof Matrix objMatrix)) {
            return false;
        }
        if (!n.equals(objMatrix.n) || !m.equals(objMatrix.m)) {
            return false;
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (!matrix[i][j].equals(objMatrix.matrix[i][j])) {
                    return false;
                }
            }
        }
        return true;
    }
}
