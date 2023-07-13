function [x, nit] = sor(A, b, x0, err, maxnit, w)
    [n, ~] = size(A);
    x = x0;
    nit = 0;
    while nit <= maxnit
        for i = 1 : n
             sum1 = 0;
            sum2 = 0;
            for j = 1 : i - 1
                sum1 = sum1 + A(i, j) * x(j);
            end
            for j = i + 1 : n
                sum2 = sum2 + A(i, j) * x0(j);
            end
            x(i) = w/A(i, i) * (b(i) - sum1 - sum2) + (1 - w) * x0(i);
        end
        if norm(x - x0, inf) <= err
            fprintf("Maximum number of iterations obtained (SOR): %d\n", nit);
            return
        end
        x0 = x;
        nit = nit + 1;
    end
    fprintf("Maximum number of iterations exceded\n");
end
