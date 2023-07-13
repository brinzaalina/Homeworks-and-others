function result = romberg(f, a, b, m, eps)
    R = zeros(m, m);
    h = b - a;
    R(1, 1) = h / 2 * (f(a) + f(b));
    for k = 2 : m
        n = 2^(k - 1);
        R(k, 1) = composite_trapezoidal(f, a, b, n);
        for j = 2 : k
            R(k, j) = (4^(j-1) * R(k, j - 1) - R(k - 1, j - 1)) / (4^(j - 1) - 1);
        end
        if abs(R(k, k) - R(k-1, k-1)) < eps
            result = R(k, k);
            break;
        else 
            continue;
        end
    end
    if k == m
         if abs(R(m, m) - R(m-1, m-1)) < eps
            result = R(m, m);
        else 
            fprintf("Precision was not met\n");
         end
    end
end