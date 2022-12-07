package Model;

public final class Task implements Runnable{
    private final int start;
    private final int end;
    private final Polynomial p1;
    private final Polynomial p2;
    private final Polynomial result;

    public Task(int start, int end, Polynomial p1, Polynomial p2, Polynomial result) {
        this.start = start;
        this.end = end;
        this.p1 = p1;
        this.p2 = p2;
        this.result = result;
    }

    @Override
    public void run() {
        for (int i = start; i < end; i++) {
            // case - no more elements to compute
            if (i > result.getCoefficients().size()) {
                return;
            }

            // find all the pairs that we add to obtain the value of the result coefficient
            for (int j = 0; j <= i; j++) {
                if (j < p1.getCoefficients().size() && (i - j) < p2.getCoefficients().size()) {
                    int val = p1.getCoefficients().get(j) * p2.getCoefficients().get(i - j);
                    result.getCoefficients().set(i, result.getCoefficients().get(i) + val);
                }
            }
        }
    }
}
