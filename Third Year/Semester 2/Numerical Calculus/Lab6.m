% 1.a)
fprintf("-----PROBLEM 1-----\n");
fprintf("a)\n");
nodes = [0, pi/2, pi, 3*pi/2, 2*pi];
y = sin(nodes);
point = pi/4;
fprintf("The value of f(%f) = %f\n", point, sin(point));
res1 = csape(nodes, y, 'variational');
val1 = fnval(res1, point);
fprintf("The value of the cubic natural spline at x = %f is %f\n", point, val1);
res2 = csape(nodes, [1 y 1], 'complete');
val2 = fnval(res2, point);
fprintf("The value of cubic clamped spline at x = %f is %f\n", point, val2);

%1.b)
t = 0 : 0.01 : 2*pi;
f = sin(t);
f1 = fnval(res1, t);
f2 = fnval(res2, t);
figure(1);
plot(t, f, t, f1, t, f2, point, sin(point), "*");

%2.
fprintf("-----PROBLEM 2-----\n");
figure(2);
[x, y] = ginput(5);
[x1, i] = sort(x);
y1 = y(i);
a = min(x);
b = max(x);
t = a : 0.01 : b;
res = csape(x1, y1, 'variational');
val = fnval(res, t);
plot(t, val, x1, y1, "*");


%3. 
fprintf("-----PROBLEM 3-----\n");
t = [0 10 20 30 40 60 80 100];
p = [0.0061 0.0123 0.0234 0.0424 0.0738 0.1992 0.4736 1.0133];
%a)
point = 45;
fprintf("a)Best linear least squares polynomial and its approx at %f: ", point);
f1 = polyfit(t, p, 1);
fprintf("f1 = %f x + %f \n", f1);
p1 = polyval(f1, point);
fprintf("f1(%f) = %f\n",point, p1);
%b)
fprintf("b)Least squares polynomial of degree 2 and its approx at %f: ", point);
f2 = polyfit(t, p, 2);
fprintf("f2 = %f x^2 + %f x + %f \n", f2);
p2 = polyval(f2, point);
fprintf("f2(%f) = %f\n", point, p2);
fprintf("Least squares polynomial of degree 3 and its approx at %f: ", point);
f3 = polyfit(t, p, 3);
fprintf("f3 = %f x^3 + %f x^2 + %f x + %f \n", f3);
p3 = polyval(f3, point);
fprintf("f3(%f) = %f\n", point, p3);
%c)
exact_value = 0.095848;
fprintf("c) Approximation errors: \n");
e1 = abs(p1 - exact_value);
e2 = abs(p2 - exact_value);
e3 = abs(p3 - exact_value);
fprintf("Linear - %f\n", e1);
fprintf("Degree 2 - %f\n", e2);
fprintf("Degree 3 - %f\n", e3);
%d)
x = 0 : 0.01 : 100;
pt1 = polyval(f1, x);
pt2 = polyval(f2, x);
pt3 = polyval(f3, x);
fi = polyfit(t, p, 7);
p_interp = polyval(fi, x);
figure(3);
hold on;
plot(t, p, "*");
plot(x, pt1, "b-");
plot(x, pt2, "g-");
plot(x, pt3, "k-");
plot(x, p_interp, "r-");
legend("Interp. points", "LSA degree 1", "LSA degree 2", "LSA degree 3", "Interp. pol.");
hold off;
