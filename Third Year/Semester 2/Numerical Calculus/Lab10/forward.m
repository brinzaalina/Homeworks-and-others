function sol = forward(A, b, n)
    x1 = b(1) ./ A(1, 1);
    sol = zeros(1,n);
    sol(1) = x1;
    for i = 2 : n
        sum = 0;
        for j = 1 : i - 1
            sum = sum + A(i, j) .* sol(j);
        end
        xi = 1 ./ A(i, i) .* (b(i) - sum);
        sol(i) = xi;
    end
end