format long
n1 = 2;
n2 = 8;
%1.
fprintf("-----EX 1-----\n");
% use Hermite => w = e^(-x^2)
f1 = @(x) x - x + 1;
fprintf("For n = 2: \n");
[I, gn, gc] = gaussian(f1, n1, 5);
I
fprintf("For n = 8: \n");
[I, gn, gc] = gaussian(f1, n2, 5);
I

%2. 
fprintf("-----EX 2-----\n");
% use Chebyshev 2nd => w = (1 - x^2)^(1/2)
f2 = @(x) x - x + 1;
fprintf("For n = 2: \n");
[I, gn, gc] = gaussian(f2, n1, 3);
I
fprintf("For n = 8: \n");
[I, gn, gc] = gaussian(f2, n2, 3);
I

%3.
fprintf("-----EX 3-----\n");
% use Legendre => w = 1
f3 = @(x) sin(x.^2);
fprintf("For n = 2: \n");
[I, gn, gc] = gaussian(f3, n1, 1);
I
fprintf("For n = 8: \n");
[I, gn, gc] = gaussian(f3, n2, 1);
I

%4.
fprintf("-----EX 4-----\n");
% use Laguerre => w = x*e^(-x), with a = 1
f4 = @(x) sin(x);
fprintf("For n = 2: \n");
[I, gn, gc] = gaussian(f4, n1, 4);
I
fprintf("For n = 8: \n");
[I, gn, gc] = gaussian(f4, n2, 4);
I

%5.
fprintf("-----EX 5-----\n");
% use Chebyshev 2nd => w = (1 - x^2)^(-1/2)
f5 = @(x) x.^2;
fprintf("For n = 2: \n");
[I, gn, gc] = gaussian(f5, n1, 2);
I
fprintf("For n = 8: \n");
[I, gn, gc] = gaussian(f5, n2, 2);
I
