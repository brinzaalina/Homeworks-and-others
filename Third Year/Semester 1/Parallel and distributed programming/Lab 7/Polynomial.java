import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public class Polynomial implements Serializable {
    private List<Integer> coefficients;

    public Polynomial(List<Integer> coefficients) {
        this.coefficients = coefficients;
    }

    public Polynomial() {
        this.coefficients = new ArrayList<>();
    }

    public Polynomial(int size) {
        this.coefficients = new ArrayList<>();
        for (int i = 0; i < size; i++) {
            this.coefficients.add(0);
        }
    }

    public void generateCoefficients() {
        Random random = new Random();
        for (int i = 0; i < this.coefficients.size(); i++) {
            var coefficient = random.nextInt(10) * (random.nextBoolean() ? 1 : -1);
            while (coefficient == 0 && i == this.coefficients.size() - 1) {
                coefficient = random.nextInt(10) * (random.nextBoolean() ? 1 : -1);
            }
            this.coefficients.set(i, coefficient);
        }
    }

    public int getDegree() {
        return this.coefficients.size() - 1;
    }

    public int getSize() {
        return this.coefficients.size();
    }

    public List<Integer> getCoefficients() {
        return this.coefficients;
    }

    public void setCoefficients(List<Integer> coefficients) {
        this.coefficients = coefficients;
    }

    public static Polynomial add(Polynomial p1, Polynomial p2) {
        int minDegree = Math.min(p1.getDegree(), p2.getDegree());
        int maxDegree = Math.max(p1.getDegree(), p2.getDegree());
        Polynomial result = new Polynomial(maxDegree + 1);
        for (int i = 0; i <= minDegree; i++) {
            result.getCoefficients().set(i, p1.getCoefficients().get(i) + p2.getCoefficients().get(i));
        }
        Polynomial remaining;
        if (p1.getDegree() > p2.getDegree()) {
            remaining = p1;
        } else {
            remaining = p2;
        }
        for (int i = minDegree + 1; i <= maxDegree; i++) {
            result.getCoefficients().set(i, remaining.getCoefficients().get(i));
        }
        return result;
    }

    public static Polynomial subtract(Polynomial p1, Polynomial p2) {
        int minDegree = Math.min(p1.getDegree(), p2.getDegree());
        int maxDegree = Math.max(p1.getDegree(), p2.getDegree());
        Polynomial result = new Polynomial(maxDegree + 1);
        for (int i = 0; i <= minDegree; i++) {
            result.getCoefficients().set(i, p1.getCoefficients().get(i) - p2.getCoefficients().get(i));
        }
        Polynomial remaining;
        if (p1.getDegree() > p2.getDegree()) {
            remaining = p1;
        } else {
            remaining = p2;
        }
        for (int i = minDegree + 1; i <= maxDegree; i++) {
            result.getCoefficients().set(i, remaining.getCoefficients().get(i));
        }

        int i = result.getCoefficients().size() - 1;
        while (i > 0 && result.getCoefficients().get(i) == 0) {
            result.getCoefficients().remove(i);
            i--;
        }
        return result;
    }

    public static Polynomial addZeros(Polynomial p, int offset) {
        List<Integer> coefficients = new ArrayList<>();
        for (int i = 0; i < offset; i++) {
            coefficients.add(0);
        }
        coefficients.addAll(p.getCoefficients());
        return new Polynomial(coefficients);
    }

    @Override
    public String toString() {
        var builder = new StringBuilder();
        if (coefficients.get(coefficients.size() - 1) != 0) {
            builder.append(coefficients.get(coefficients.size() - 1)).append("x^").append(coefficients.size() - 1);
        }
        for (var i = coefficients.size() - 1 - 1; i > 0; i--) {
            if (coefficients.get(i) != 0) {
                if (coefficients.get(i) > 0) {
                    builder.append("+");
                }
                builder.append(coefficients.get(i)).append("x^").append(i);
            }
        }
        if (coefficients.get(0) != 0) {
            if (coefficients.get(0) > 0) {
                builder.append("+");
            }
            builder.append(coefficients.get(0));
        }
        return builder.toString();
    }
}
