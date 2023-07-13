function result = composite_trapezoidal(f, a, b, n)
    h = (b - a) / n;
    xi = a : h : b;
    len = length(xi);
    sum = 0;
    for i = 2 : len - 1
        sum = sum + f(xi(i));
    end
    sum = sum .* 2 + f(a) + f(b);
    result = h ./ 2 * sum;
end