clear
clc
close all

%A food store owner receives 1-liter bottles from two suppliers.
%After some complaints from customers, he wants to check the accuracy of
%the weigths of 1-liter water bottles. He finds the following weigths (the
%two populations are approximately normally distributed):
x=[1021, 980, 1017, 988, 1005, 998, 1014, 985, 995, 1004, 1030, 1015, 995, 1023];
y=[1070, 970, 993, 1013, 1006, 1002, 1014, 997, 1002, 1010, 975];

n1=length(x);
n2=length(y); %length of each array
mx=mean(x);
my=mean(y); %mean for each set of values
sx=var(x);
sy=var(y); %variances for each set of values

alpha=0.05; %significance level

%a) At 5% significance level, do the population variances seem to differ?
%Null hypothesis: the population variances are equal.
%Alternative hypothesis: the population variances differ.

typea=0; %two tailed test
fprintf('a)\n')
fprintf('SIGNIFICANCE LEVEL %f:\n',alpha)
fprintf("We are doing a two-tailed test for variances.\n");
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

%b)At the same significance level, on average, does Supplier A seem to be
%more reliable?
%From a), we find if the variances of the populations are equal or not and
%we have to use this information here.
%In this case, the null hypothesis is that the means are equal.
%The alternative hypothesis is that the mean of the supplier A is greater
%than the one for supplier B.
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
    fprintf('The null hypothesis is rejected (t in RR), i.e. Supplier A is more reliable.\n')
else
    fprintf('The null hypothesis is NOT rejected (t not in RR), i.e. Supplier A is not more reliable.\n')
end  