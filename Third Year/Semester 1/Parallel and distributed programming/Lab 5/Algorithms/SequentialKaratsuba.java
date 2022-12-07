package Algorithms;

import Model.Polynomial;
import Utils.PolynomialUtils;

public class SequentialKaratsuba {
    public static Polynomial multiply(Polynomial p1, Polynomial p2) {
        if (p1.getDegree() < 2 || p2.getDegree() < 2) {
            return SequentialClassic.multiply(p1, p2);
        }

        int len = Math.max(p1.getDegree(), p2.getDegree()) / 2;
        Polynomial lowP1 = new Polynomial(p1.getCoefficients().subList(0, len));
        Polynomial highP1 = new Polynomial(p1.getCoefficients().subList(len, p1.getCoefficients().size()));
        Polynomial lowP2 = new Polynomial(p2.getCoefficients().subList(0, len));
        Polynomial highP2 = new Polynomial(p2.getCoefficients().subList(len, p2.getCoefficients().size()));

        Polynomial z1 = multiply(lowP1, lowP2);
        Polynomial z2 = multiply(PolynomialUtils.add(lowP1, highP1), PolynomialUtils.add(lowP2, highP2));
        Polynomial z3 = multiply(highP1, highP2);

        // compute final result
        Polynomial r1 = PolynomialUtils.addZeros(z3, 2 * len);
        Polynomial r2 = PolynomialUtils.addZeros(PolynomialUtils.subtract(PolynomialUtils.subtract(z2, z3), z1), len);
        return PolynomialUtils.add(PolynomialUtils.add(r1, r2), z1);
    }
}
