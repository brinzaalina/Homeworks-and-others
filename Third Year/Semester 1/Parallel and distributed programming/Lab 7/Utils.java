public class Utils {
    public static Polynomial getResult(Object[] polynomials) {
        int size = ((Polynomial) polynomials[0]).getDegree();
        Polynomial result = new Polynomial(size + 1);
        for (Object polynomial: polynomials) {
            result = Polynomial.add(result, (Polynomial) polynomial);
        }
        return result;
    }

    public static Polynomial multiplySequence(Polynomial p1, Polynomial p2, int start, int end) {
        Polynomial result = new Polynomial(2 * p1.getDegree() + 1);
        for (int i = start; i < end; i++) {
            for (int j = 0; j < p2.getCoefficients().size(); j++) {
                result.getCoefficients().set(i + j, result.getCoefficients().get(i + j) + p1.getCoefficients().get(i) * p2.getCoefficients().get(j));
            }
        }
        return result;
    }

    public static Polynomial regularSequential(Polynomial p1, Polynomial p2) {
        Polynomial result = new Polynomial(p1.getDegree() + p2.getDegree() + 1);
        for (int i = 0; i < p1.getCoefficients().size(); i++) {
            for (int j = 0; j < p2.getCoefficients().size(); j++) {
                result.getCoefficients().set(i + j, result.getCoefficients().get(i + j) + p1.getCoefficients().get(i) * p2.getCoefficients().get(j));
            }
        }
        return result;
    }

    public static Polynomial KaratsubaSequential(Polynomial p1, Polynomial p2) {
        if (p1.getDegree() < 2 || p2.getDegree() < 2) {
            return regularSequential(p1, p2);
        }

        int m = Math.min(p1.getDegree(), p2.getDegree()) / 2;
        Polynomial low1 = new Polynomial(p1.getCoefficients().subList(0, m));
        Polynomial high1 = new Polynomial(p1.getCoefficients().subList(m, p1.getSize()));
        Polynomial low2 = new Polynomial(p2.getCoefficients().subList(0, m));
        Polynomial high2 = new Polynomial(p2.getCoefficients().subList(m, p2.getSize()));
        Polynomial z0 = KaratsubaSequential(low1, low2);
        Polynomial z1 = KaratsubaSequential(Polynomial.add(low1, high1), Polynomial.add(low2, high2));
        Polynomial z2 = KaratsubaSequential(high1, high2);
        Polynomial result1 = Polynomial.addZeros(z2, 2 * m);
        Polynomial result2 = Polynomial.addZeros(Polynomial.subtract(Polynomial.subtract(z1, z2), z0), m);
        return Polynomial.add(Polynomial.add(result1, result2), z0);
    }
}
