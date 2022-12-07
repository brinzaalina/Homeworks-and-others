package Model;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public class Polynomial {
    private List<Integer> coefficients;
    private int degree;

    public Polynomial(List<Integer> coefficients) {
        this.coefficients = coefficients;
        this.degree = coefficients.size() - 1;
    }

    private void generateCoefficients(int degree) {
        coefficients = new ArrayList<>();
        var r = new Random();
        for (int i = 0; i <= degree; i++) {
            var coefficient = r.nextInt(10) * (r.nextBoolean() ? 1 : -1);
            while (coefficient == 0 && i == degree) {
                coefficient = r.nextInt(10) * (r.nextBoolean() ? 1 : -1);
            }
            coefficients.add(coefficient);
        }
    }

    public Polynomial(int degree) {
        this.degree = degree;
        generateCoefficients(degree);
    }

    public List<Integer> getCoefficients() {
        return coefficients;
    }

    public int getDegree() {
        return degree;
    }

    public void setCoefficients(List<Integer> coefficients) {
        this.coefficients = coefficients;
    }

    public void setDegree(int degree) {
        this.degree = degree;
    }

    @Override
    public String toString() {
        var builder = new StringBuilder();
        if (coefficients.get(degree) != 0) {
            builder.append(coefficients.get(degree)).append("x^").append(degree);
        }
        for (var i = degree - 1; i > 0; --i) {
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
