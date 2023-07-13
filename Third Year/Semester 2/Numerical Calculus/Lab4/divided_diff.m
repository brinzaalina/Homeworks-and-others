function dd = divided_diff(x, f)
    n = length(x);
    dd = [f', zeros(n, n - 1)];
    for k = 2 : n
        for i = 1 : n - k + 1
            dd(i, k) = (dd(i + 1, k - 1) - dd(i, k - 1)) / (x(i + k - 1) - x(i));
        end
    end
end