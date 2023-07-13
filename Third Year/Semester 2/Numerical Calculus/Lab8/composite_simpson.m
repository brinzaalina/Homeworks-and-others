function result = composite_simpson(f, a, b, n)
    h = (b - a) / n;
    xi = a : h : b;
    sum1 = 0;
    sum2 = 0;
    m = length(xi) / 2;
    for i = 1 : m
        sum1 = sum1 + f(xi(2 * i));
    end
    for i = 1 : m - 1 
        sum2 = sum2 + f(xi(2 * i + 1));
    end
    sum = f(a) + 4 .* sum1 + 2 .* sum2 + f(b);
    result = h / 3 .* sum;
end