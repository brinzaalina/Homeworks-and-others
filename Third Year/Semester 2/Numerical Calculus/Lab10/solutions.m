% 1.
fprintf('-----EX 1-----\n');
n = 5
A = 5 * eye(n) - diag(ones(n - 1, 1), -1) - diag(ones(n - 1, 1), 1);
b = 3 * ones(n ,1) + triu(ones(n, 1)) + tril(ones(n, 1), 1 - n);

sol1 = gauss(A, b, n)
sol2 = factorization(A, b, n, 'LUP')
sol3 = factorization(A, b, n, 'Cholesky')
sol4 = factorization(A, b, n, 'QR')

%2.
fprintf('-----EX 2-----\n');
n = 7
A = 5 * eye(n) - diag(ones(n-1, 1), 1) - diag(ones(n-1, 1), -1) - diag(ones(n-3, 1), 3) - diag(ones(n-3, 1), -3);
b = ones(n ,1) + triu(ones(n, 1)) + tril(ones(n, 1), 1 - n) + triu(ones(n, 1), -2) + tril(ones(n, 1), 3 - n);

sol1 = gauss(A, b, n)
sol2 = factorization(A, b, n, 'LUP')
sol3 = factorization(A, b, n, 'Cholesky')
sol4 = factorization(A, b, n, 'QR')