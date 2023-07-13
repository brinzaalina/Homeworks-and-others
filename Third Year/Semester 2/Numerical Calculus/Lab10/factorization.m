function sol = factorization(A, b, n, type)
    switch type
        case 'LUP'
            [L, U, P] = lu(A);
            y = forward(L, P * b, n);
            sol = backward(U, y, n);
        case 'Cholesky'
            U = chol(A);
            y = forward(U', b, n);
            sol = backward(U, y, n);
        case 'QR'
            [Q, R] = qr(A);
            sol = backward(R, Q' * b, n);
    end
end