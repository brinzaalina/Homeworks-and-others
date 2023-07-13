%I
b = [4; 5; 6];
c = a*b;
d = b';
e = a.*d;
f = a.^2;
g = a.^d;
v = 1:6;
w = 2:3:10;
y = 10:-1:0;
exp(a);
exp(1);
sqrt(a);
m = max(a);
[m, k] = max(a);
h = [-2 -9 8];
k = abs(h);
mean(a);
geomean(a);
sum(a);
prod(a);

%II
a = [1 2 13; 4 5 6; 7 8 9];
b = [4 8 12; -1 0 5; 2 3 8];
[m, n] = size(a);
t = b';
c = a*b;
d = a.*b;
e = a.^2;
size(a);
length(a);
m = mean(a);
m1 = mean(a,2);
g = geomean(a);
s = sum(a);
s1 = sum(a, 2);
p = prod(a);
p1 = prod(a,2);
max(a);
min(a);
diag(a);
m>2;
a>b;
inv(b);
det(b);
f=abs(b);
b=[16 15 24]';
x=a\b;
triu(a);
tril(b);
m=[2 3 5; 7 11 13; 17 19 23];
m(2,1);
m(:,1);
m(2,:);
m(2, 1:2);
m(2, 2:end);
m(2:3, 2:3);
eye(8);
eye(5,7);
zeros(5,7);
ones(7,9);
M=magic(4);
sum(M);
sum(M,2);
sum(diag(M));
sum(diag(fliplr(M)));

%II
%1.
p = [2 -5 0 8]
polyval(p,2)
%2.
p = [1 -5 -17 21]
roots(p)

%III
sa=3;
sb=3;
%1.
subplot(sa,sb,1);
x = 0:0.01:1;
y = exp(10*x.*(x-1)).*sin(12*pi*x);
plot(x,y)
title('Ex 1.a')

subplot(sa,sb,2);
x1 = 0:0.01:1;
y1 = 3*exp(5*x.^2-1).*cos(12*pi*x);
plot(x1,y1)
title('Ex 1.b')

%2. plot(x,y)
subplot(sa,sb,3);
a = 5;
b = 10;
t = 0:0.01:10*pi;
x1 = (a + b)*cos(t) - b*cos((a/b + 1).*t);
y1 = (a + b)*sin(t) - b*sin((a/b + 1).*t);
plot(x1,y1)
title('Ex 2')

%3.plot(x,f1) hold on plot(...) hold off or plot(x,f1,x, f2, x, f3)
subplot(sa,sb,4);
x = 0:0.01:2*pi;
f1 = cos(x);
f2 = sin(x);
f3 = cos(2*x);
plot(x,f1,x,f2,x,f3)
title('Ex 3')

%4.
subplot(sa,sb,5);
x1 = -1:0.01:0;
x2 = 0:0.01:1;
f1 = x1.^3 + sqrt(1-x1);
f2 = x2.^3 - sqrt(1-x2);
plot(x1,f1,x2,f2)
title('Ex 4')

%5.
subplot(sa,sb,6);
x1 = 0:2:50;
x2 = 1:2:49;
f1 = x1/2;
f2 = 3*x2 + 1;
plot(x1,f1,'*',x2,f2, '*')
title('Ex 5')

%6. write a function to compute general case 
g=1+ 1/(1+ 1/(1 + 1/(1 + 1/(1 + 1/(1+1)))))

%7. [x,y]=meshgrid(-2:0.01:2, -4:0.01:4) mesh(x,y,g)
subplot(sa,sb,7);
[x,y]=meshgrid(-2:0.01:2, -4:0.01:4);
g = exp(-((x - 1/2).^2 + (y - 1/2).^2));
mesh(x,y,g)
title('Ex 7')