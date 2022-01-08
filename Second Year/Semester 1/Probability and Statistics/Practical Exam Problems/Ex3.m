clear
clc
close all

%Nickel powders are used in coatings used to shield electronic equipment. A
%random sample is selected and the sizes of nickel particles in each
%coating are recorded (they are assumed to be approximately normally
%distributed):
x=[3.26, 1.89, 2.42, 2.03, 3.07, 2.95, 1.39, 3.06, 2.46, 3.35, 1.56, 1.79, 1.76, 3.82, 2.42, 2.96];
n=length(x);
m=mean(x);
s=std(x);
%a) At the 5% significance level, on average, do these nickel particles
%seem to be smaller than 3?
%Null hypothesis: The mean is equal to 3. 
%Alternative hypothesis: The mean is smaller than 3.
m0=3;
fprintf('a)\n');
fprintf('We are doing a left-tailed test for the mean when we do not know the standard deviation.\n');
type=-1;
alpha1=0.05; %significance level
fprintf('SIGNIFICANCE LEVEL %f:\n',alpha1)
[h, p, ci, valstat] = ttest(x, m0, alpha1, type);
t1=(m-m0)/s*sqrt(n);
RR_Ttest(alpha1, n, type);
fprintf('The value of the test statistic t is %f (given by ttest %f).\n', t1, valstat.tstat);
fprintf('The P-value of the test is %.10f.\n',p)
if h==1
    fprintf('The null hypothesis is rejected (t in RR), i.e. the nickel particles seem to be smaller than 3.\n')
else
    fprintf('The null hypothesis is not rejected (t not in RR), i.e. the nickel particles seem to not be smaller than 3.\n')
end

%b) Find a 99% confidence interval for the standard deviation of the size of
%the nickel particles.
fprintf('b)\n');
alpha2=0.01;
[li,ri]=ConfIntVar(x,alpha2);
fprintf('Confidence interval for the standard deviation:\n')
fprintf('(%.4f, %.4f)\n', sqrt(li), sqrt(ri))