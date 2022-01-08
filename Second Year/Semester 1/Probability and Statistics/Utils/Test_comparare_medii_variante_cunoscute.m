clear 
clc
close all

x=[141,   138,   136,   142,   145,   140,   139,   137,   132,   140];

y=[137,   138,   133,   130,   131,   139,   140,   138,   135,   129];

n1=length(x);
n2=length(y);
mx=mean(x);
my=mean(y);
s1=2;
s2=6;

alpha=0.05; % significance level

type=0; %two-tailed test
fprintf('a)\n')
fprintf('\n')
fprintf('SIGNIFICANCE LEVEL %f:\n',alpha)

zz=abs(mx-my)/sqrt(s1^2/n1+s2^2/n2);%test statistic

[l,r]=RR_Ztest(alpha,type);

if (abs(zz)<r)&(abs(zz)>l)
    fprintf('The null hypothesis is NOT rejected \n')
else
    fprintf('The null hypothesis is rejected \n')
end    
