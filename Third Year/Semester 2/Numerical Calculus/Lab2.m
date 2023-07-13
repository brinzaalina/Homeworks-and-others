% 1. 
figure(1);
x = 0 : 0.01 : 1;
subplot(2, 2, 1);
f1 = x;
plot(x, f1);
title('l1(x) = x');

subplot(2, 2, 2);
f2 = 3/2 * x.^2 - 1/2;
plot(x, f2);
title('l2(x) = 3/2 * x^2 - 1/2');

subplot(2, 2, 3);
f3 = 5/2 * x.^2 - 3/2 * x;
plot(x, f3);
title('l3(x) = 3/2 * x^2 - 3/2 * x');

subplot(2, 2, 4);
f4 = 35/8 * x.^4 - 15/3 * x.^2 + 3/8;
plot(x, f4);
title('l4(x) = 35/8 * x.^4 - 15/4 * x.^2 + 3/8');

%2. a)
figure(2);
t = -1 : 0.01 : 1;
T1 = cos(acos(t));
T2 = cos(2 .* acos(t));
T3 = cos(3 .* acos(t));

plot(t, T1, t, T2, t, T3);

%2. b)
figure(3);
n = 8;
x = -1 : 0.01 : 1;
T0 = 1;
T1 = x;
hold on
plot(x, T0, x, T1);
for i = 2 : n
    T2 = 2 .* x .* T1 - T0;
    plot(x, T2);
    T0 = T1;
    T1 = T2;
end
hold off

%3.
figure(4);
x = -1 : 0.01 : 3;
x0 = 0;
n = 6;
prev_f = ((x - x0) .^ 0 / factorial(0)) .* exp(x0);
hold on 
plot(x, prev_f);
for i = 1 : n - 1
    p = prev_f + (x - x0).^i / factorial(i);
    plot(x, p);
    prev_f = p;
end
hold off

%4.
h = 0.25;
x = [];
n = 6;
for i = 0: n
    x = [x 1+i*h];
end
x
f = sqrt(5 * x.^2 + 1);
f
t = [f];
prev_t = f;
for i = 1:n
    new_t = [];
    for j = 1:n-i+1
        new_t = [new_t prev_t(j + 1) - prev_t(j)];
    end
    new_t = [new_t zeros(1, i)];
    t = [t; new_t];
    prev_t = new_t;
end
t'

%5.
x = [2 4 6 8];
n = 4;
f = [4 8 14 16];
t = [x ; f];
for i = 2:n
    new_t = [];
    for j = 1:n-i+1
        new_t = [new_t (t(i, j + 1) - t(i, j)) / (t(1, j+i-1) - t(1, j))];
    end
    new_t = [new_t zeros(1, i - 1)];
    t = [t ; new_t];
    prev_t = new_t;
end
t'


