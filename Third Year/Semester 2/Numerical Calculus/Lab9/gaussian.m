function [I, gn, gc] = gaussian(f, n, case_nr)
    alpha = zeros(1, n);
    switch case_nr
        case 1
            beta = [2, (4 - ([1:n-1]).^(-2)).^(-1)];
        case 2
            beta = [pi, 1/2, 1/4 .* ones(1, n-2)];
        case 3
            beta = [pi/2, 1/4 .* ones(1, n - 1)];
        case 4
            a = input("a=");
            k = 1 : n-1;
            alpha = [a + 1, 2 * k + a + 1];
            beta = [gamma(1+a), k.*(k + a)];
        case 5
            beta = [sqrt(pi), ([1:n-1])/2];
    end
    
    J = diag(alpha) + diag(sqrt(beta(2:n)), -1) + diag(sqrt(beta(2:n)), 1);
    [v, d] = eig(J);
    gn = diag(d);
    gc = beta(1) * v(1, :).^2;
    I = gc * f(gn);
end