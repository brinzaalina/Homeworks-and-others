clear
clc
close all

%A study is conducted to compare heat loss in glass pipes versus steel pipes
%of the same size. Various liquids at identical starting temperatures are
%run through segments of each type and the heat loss (in Celsius) is
%measured. These data result (normality of the two populations is assumed):
x = [4.6, 0.7, 4.2, 1.9, 4.8, 6.1, 4.7, 5.5, 5.4];
y = [2.5, 1.3, 2.0, 1.8, 2.7, 3.2, 3.0, 3.5, 3.4];
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

%b) At the same significance level, does it seem that on average, steel
%pipes lose more heat than glass pipes?
%Null hypothesis: the means are equal.
%Alternative hypothesis: the means are not equal.
fprintf('b)\n');
fprintf('SIGNIFICANCE LEVEL %f:\n',alpha)
fprintf('We are doing a right-tailed test for the difference of means.\n');
typeb=1; %right-tailed test 
if ha==0 
   vartype='equal';
   n=n1+n2-2;
   t=(mx-my)/sqrt((n1-1)*sx+(n2-1)*sy)*sqrt((n1+n2-2)/(1/n1+1/n2));
else
   vartype='unequal';
   c=(sx/n1)/(sx/n1+sy/n2);
   n=ceil(1/(c^2/(n1-1)+(1-c)^2/(n2-1)));
   t=(mx-my)/sqrt(sx/n1+sy/n2);
end
RR_Ttest(alpha,n,typeb); %rejection region 
[hb,pb,cib,valstatb]=ttest2(x,y,alpha,typeb,vartype);
fprintf('The value of the test statistc t is %f (given by ttest2 %f).\n',t,valstatb.tstat)
fprintf('The P-value of the test is %.10f.\n',pb)
if hb==1
    fprintf('The null hypothesis is rejected (t in RR), i.e. steel pipes seem to lose more heat.\n')
else
    fprintf('The null hypothesis is NOT rejected (t not in RR), i.e. steel pipes seem to not lose more heat than glass pipes.\n')
end  