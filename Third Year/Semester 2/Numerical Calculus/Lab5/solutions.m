%1.
format long
fprintf("-----PROBLEM 1-----\n");
time = [0 3 5 8 13];
distance = [0 225 383 623 993];
speed = [75 77 80 74 72];
t = 10;
position_t = hermite(time, distance, speed, t);
eps = 0.001;
position_t_eps = hermite(time, distance, speed, t + eps);
speed_t = (position_t_eps - position_t) / eps;
fprintf("The position at time t = %f is %f and the speed is %f\n", t, position_t, speed_t);

%2.
fprintf("-----PROBLEM 2-----\n");
x = [1 2];
f = [0 0.6931];
d = [1 0.5];
t = 1.5;
sol = hermite(x, f, d, t);
fprintf("f(1.5) is approx. %f\n", sol);
abs_err = abs(log(t) - sol);
fprintf("Absolute approx. error: %f\n", abs_err);

%3. 
fprintf("-----PROBLEM 3-----\n");
figure(1);
x = linspace(-5, 5, 15);
f = sin(2.*x);
d = 2.*cos(2.*x);
xx = -5 : 0.01 : 5;
sol = [];
for i = 1 : length(xx)
    sol = [sol hermite(x, f, d, xx(i))];
end
fn = sin(2.*xx);
plot(xx, fn, 'r', xx, sol, 'b');