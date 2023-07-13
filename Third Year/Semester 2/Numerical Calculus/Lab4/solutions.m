%1.
fprintf("-----PROBLEM 1-----\n");
x = [1 1.5 2 3 4];
f = [0 0.17609 0.30103 0.47712 0.60206];
val = [2.5 3.25];
i = [10 : 35];
yi = i ./ 10;
sol = newton(x, f, val)
N = newton(x, f, yi);
E = max(abs(log10(yi) - N));
fprintf("Maximum interpolation error is %f \n", E);

%2.
fprintf("-----PROBLEM 2-----\n");
x = [1 2 3 4 5];
f = [22 23 25 30 28];
val = [2.5];
sol = newton(x, f, val)
figure(1);
plot(x, f, "r*");
hold on;

vals = 1: 0.01 : 5;
N = newton(x, f, vals);
plot(vals, N, "b");

%3.
figure(2);
X = 0 : 0.01 : 6;
f = @(x) exp(sin(x));
plot(X, f(X), 'g');
x = linspace(0, 6, 13);
y = newton(x, f(x), X);
hold on;
plot(X, y, 'b');
plot(x, f(x), 'r*');

%4.
fprintf("-----PROBLEM 4-----\n");
x = [64 81 100 121 144 169];
f = [8 9 10 11 12 13];
err = 1e-3;
sol = aitken(x, f, 115, err);
fprintf("Approx: %f, actual value: %f \n", sol, sqrt(115));