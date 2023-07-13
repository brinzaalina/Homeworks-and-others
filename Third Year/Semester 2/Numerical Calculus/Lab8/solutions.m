% Applications
% 1. ln 2 is the integral from 0 to 1 from 1 / 1 + x
fprintf("-----PROBLEM 1-----\n");
f = @(x) 1/x;
a = 1;
b = 2;
n1 = 13;
n2 = 19;
n3 = 6;
comp_rect = composite_rectangle(f, a, b, n1)
comp_trap = composite_trapezoidal(f, a, b, n2)
comp_sim = composite_simpson(f, a, b, n3)

% 2.
fprintf("-----PROBLEM 2-----\n");
f = @(x) exp(-x.^2);
a = 0;
b = 1;
n = 16;
eps = 0.001;
ad_rect = adaptive_quadrature(f, a, b, eps, @composite_rectangle, n)
ad_trap = adaptive_quadrature(f, a, b, eps, @composite_trapezoidal, n)
ad_sim = adaptive_quadrature(f, a, b, eps, @composite_simpson, n)

% 3.
fprintf("-----PROBLEM 3-----\n");
f = @(x) 1/(2 + cos(x));
a = 0;
b = 2 .* pi;
n = 16;
eps = 0.001;
result = romberg(f, a, b, n, eps)