function [x, nit] = jacobi(A, b, x0, err, maxnit)
    [n, ~] = size(A);
    x = x0;
    nit = 0;
    while nit <= maxnit
        for i = 1 : n
            sum = 0;
            for j = 1 : n
                if i ~= j
                    sum = sum + A(i, j) * x0(j);
                end
            end
            x(i) = 1 / A(i, i) * (b(i) - sum);
        end
        
        if norm(x - x0, inf) <= err
            fprintf("Maximum number of iterations obtained (Jacobi): %d\n", nit);
            return
        end
        
        x0 = x;
        nit = nit + 1;
    end
    fprintf("Maximum number of iterations exceded\n");
end