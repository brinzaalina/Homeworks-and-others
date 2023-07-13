% 1.
fprintf('-----EX 1-----\n');
n = 5
A = 5 * eye(n) - diag(ones(n - 1, 1), -1) - diag(ones(n - 1, 1), 1);
b = 3 * ones(n ,1) + triu(ones(n, 1)) + tril(ones(n, 1), 1 - n);
x0 = zeros(n, 1);
[sol11, it11] = jacobi(A, b, x0, 0.0001, 20)
[sol12, it12] = jacobi_matrix(A, b, x0, 0.0000000001, 30)
[sol13, it13] = gauss_seidel(A, b, x0, 0.0001, 10)
[sol14, it14] = gauss_seidel_matrix(A, b, x0, 0.0000000001, 15)
T = inv(diag(diag(A))) * (-1) * (tril(A, -1) + triu(A, 1));
w = 2 / (1 + sqrt(1 - (max(abs(eig(T)))^2)));
[sol15, it15] = sor(A, b, x0, 0.00001, 25, w)
[sol16, it16] = sor_matrix(A, b, x0, 0.0000000001, 55, w)

%2.
fprintf('-----EX 2-----\n');
n = 7
A = 5 * eye(n) - diag(ones(n-1, 1), 1) - diag(ones(n-1, 1), -1) - diag(ones(n-3, 1), 3) - diag(ones(n-3, 1), -3);
b = ones(n ,1) + triu(ones(n, 1)) + tril(ones(n, 1), 1 - n) + triu(ones(n, 1), -2) + tril(ones(n, 1), 3 - n);
x0 = zeros(n, 1);
[sol21, it21] = jacobi(A, b, x0, 0.00001, 30)
[sol22, it22] = jacobi_matrix(A, b, x0, 0.0000000001, 50)
[sol23, it23] = gauss_seidel(A, b, x0, 0.00001, 15)
[sol24, it24] = gauss_seidel_matrix(A, b, x0, 0.0000000001, 30)
T = inv(diag(diag(A))) * (-1) * (tril(A, -1) + triu(A, 1));
w = 2 / (1 + sqrt(1 - (max(abs(eig(T)))^2)));
[sol25, it25] = sor(A, b, x0, 0.00001, 45, w)
[sol26, it26] = sor_matrix(A, b, x0, 0.0000000001, 90, w)