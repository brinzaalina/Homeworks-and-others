function result = composite_rectangle(f, a, b, n)
    h = (b-a) ./ n;
    sum = 0;
    for i = 0 : n - 1
        x = a + (i + 1/2) .* h;
        sum = sum + f(x);
    end
    result = h * sum;
end