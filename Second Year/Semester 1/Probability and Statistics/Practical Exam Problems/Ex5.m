clear
clc
close all

%To reach the maximum efficiency in performing an assembling operation in a
%manufacturing plant, new employees are required to take a 1-month training
%course. A new method was suggested, and the manager wants to compare the
%new method with the standard one, by looking at the lengths of time
%required for employees to assemble a certain device. They are given below
%(and assumed approximately normally distributed):
x = [46, 37, 39, 48, 47, 44, 35, 31, 44, 37];
y = [35, 33, 31, 35, 34, 30, 27, 32, 31, 31];
n1 = length(x);
n2 = length(y);
mx = mean(x);
my = mean(y);
sx = var(x);
sy = var(y);

%a) At the 5% significance level, do the population variances seem to
%differ?
%Null hypothesis: the variances are equal.
%Alternative hypothesis: the variances are different.
fprintf('a)\n');
fprintf('We are doing a two-test for the variances.\n');
typea = 0;
alpha = 0.05;
RR_Ftest(alpha,n1-1,n2-1,typea); %find the rejection region
[ha, pa, cia, valstata] = vartest2(x, y, alpha, typea); 
f=sx/sy;
fprintf('The value of the test statistic f is %f (given by vartest2 %f).\n',f,valstata.fstat)
fprintf('The P-value of the test is %f.\n',pa)
if ha==1
    fprintf('The null hypothesis is rejected (f in RR), i.e. the variances seem to be different.\n')
else
    fprintf('The null hypothesis is NOT rejected (f not in RR), i.e. the variances seem to be equal.\n')
end    

%b) Find a 95% confidence interval for the difference of the average
%assembling times.
fprintf('b)\n');
if ha==1
    [li, ri] = ConfIntDifMeanNotVarDif(x, y, alpha);
else
    [li, ri] = ConfIntDifMeanNotVarEq(x, y, alpha);
end
fprintf('Confidence interval for the difference of the means(%.4f,%.4f)\n',li,ri)