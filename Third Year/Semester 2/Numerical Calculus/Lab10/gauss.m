function sol = gauss(A, b, n)
    for column = 1 : n - 1
        [val, q] = max(abs(A(column:n, column)));
        q = q + column - 1;
        if column ~= q
            A([column, q], :) = A([q, column], :);
            b([column, q]) = b([q, column]);
        end
        for row = column + 1 : n
            val = A(row, column) / A(column, column);
            b(row) = b(row) - val * b(column);
            A(row, column : n) = A(row, column : n) - val * A(column, column : n);
        end
    end
    
    if A(n, n) == 0
        sol = -1;
        return
    end
    
    sol = backward(A, b, n);
end