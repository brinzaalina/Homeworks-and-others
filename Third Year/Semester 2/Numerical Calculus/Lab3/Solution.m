%1.
format long
years = [1930 1940 1950 1960 1970 1980];
population = [123203 131669 150697 179323 203212 226505];
round(Lagrange(years, population, [1955, 1995]))

%2.
nodes = [81, 100, 121];
func = [9, 10, 11];
vals = [115];

sqrt(115)
Lagrange(nodes, func, vals)

%3.
x = linspace(0, 10, 21);
t = 0:0.01:10;
f = (1 + cos(pi * t)) ./ (1 + t);
lagF = (1 + cos(pi * x)) ./ (1 + x);
sol = Lagrange(x, lagF, t);
subplot(1, 2, 1);
plot(t, f);
ylim([0, 2]);
title("Actual function");

subplot(1, 2, 2);
plot(t, sol);
ylim([0, 2]);
title("Lagrange interpolation");