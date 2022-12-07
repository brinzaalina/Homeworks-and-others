package Utils;

import Model.Polynomial;

import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

public class PolynomialUtils {
    public static Polynomial add(Polynomial p1, Polynomial p2) {
        int minDegree = Math.min(p1.getDegree(), p2.getDegree());
        int maxDegree = Math.max(p1.getDegree(), p2.getDegree());
        List<Integer> coefficients = new ArrayList<>(maxDegree + 1);

        // Add the two polynomials
        for (int i = 0; i <= minDegree; i++) {
            coefficients.add(p1.getCoefficients().get(i) + p2.getCoefficients().get(i));
        }

        if (minDegree != maxDegree) {
            if (maxDegree == p1.getDegree()) {
                for (int i = minDegree + 1; i <= maxDegree; i++) {
                    coefficients.add(p1.getCoefficients().get(i));
                }
            } else {
                for (int i = minDegree + 1; i <= maxDegree; i++) {
                    coefficients.add(p2.getCoefficients().get(i));
                }
            }
        }
        return new Polynomial(coefficients);
    }

    public static Polynomial subtract(Polynomial p1, Polynomial p2) {
        int minDegree = Math.min(p1.getDegree(), p2.getDegree());
        int maxDegree = Math.max(p1.getDegree(), p2.getDegree());
        List<Integer> coefficients = new ArrayList<>(maxDegree + 1);

        // Subtract the two polynomials
        for (int i = 0; i <= minDegree; i++) {
            coefficients.add(p1.getCoefficients().get(i) - p2.getCoefficients().get(i));
        }

        if (minDegree != maxDegree) {
            if (maxDegree == p1.getDegree()) {
                for (int i = minDegree + 1; i <= maxDegree; i++) {
                    coefficients.add(p1.getCoefficients().get(i));
                }
            } else {
                for (int i = minDegree + 1; i <= maxDegree; i++) {
                    coefficients.add(-p2.getCoefficients().get(i));
                }
            }
        }

        int i = coefficients.size() - 1;
        if (i > 0 && coefficients.get(i) == 0) {
            coefficients.remove(i);
        }
        return new Polynomial(coefficients);
    }

    public static Polynomial addZeros(Polynomial p, int offset) {
        List<Integer> coefficients = IntStream.range(0, offset).mapToObj(i -> 0).collect(Collectors.toList());
        coefficients.addAll(p.getCoefficients());
        return new Polynomial(coefficients);
    }
}
