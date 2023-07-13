function sol = backward(A, b, n)
    xn = b(n) ./ A(n, n);
    sol = zeros(1,n);
    sol(n) = xn;
    for i = n - 1: -1 : 1
        sum = 0;
        for j = i + 1 : n
            sum = sum + A(i, j) .* sol(j);
        end
        xi = 1 ./ A(i, i) .* (b(i) - sum);
        sol(i) = xi;
    end
end