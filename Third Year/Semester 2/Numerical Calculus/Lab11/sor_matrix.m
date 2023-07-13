function [x, nit] = sor_matrix(A, b, x0, err, maxnit, w)
    D = diag(diag(A));
    L = (-1) * tril(A, -1);
    U = (-1) * triu(A, 1);
    T = inv(1/w * D - L) * ((1-w)/w * D + U);
    c = inv(1/w * D - L) * b;
    x = x0;
    for nit = 1 : maxnit
        x = T * x0 + c;
        if norm(x-x0, inf) <= (1-norm(T, inf)) / norm(T, inf) * err
            fprintf("Maximum number of iterations obtained (SOR matrix): %d\n", nit);
            return
        end
        x0 = x;
    end
    fprintf("Maximum number of iterations exceded\n");
end