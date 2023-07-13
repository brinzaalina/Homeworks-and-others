function result = adaptive_quadrature(f, a, b, eps, met, m)
    i1 = met(f, a, b, m);
    i2 = met(f, a, b, 2 * m);
    if abs(i1 - i2) < eps
        result = i2;
        return
    else
        result = adaptive_quadrature(f, a, (a + b) / 2, eps, met, m) + adaptive_quadrature(f, (a + b) / 2, b, eps, met, m);
    end
end