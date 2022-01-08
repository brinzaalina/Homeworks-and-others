clc
clear
close all

x=[71.6,  88.7,  92.1,  72.0,  68.2,  79.9,  73.2,  75.3,  86.4,  82.6];
n=length(x);
fprintf(' Volume %d \n',n)
med=mean(x);
fprintf(' Sample mean %f\n',med)
sigma=5;
s2=var(x);
fprintf(' Sample standard deviation %f\n',sqrt(s2))


type=0; %bilateral test

alpha=0.05; %significance level

fprintf('\n')
fprintf('SIGNIFICANCE LEVEL %f:\n',alpha)
[h, p, ci1, vstat] = vartest(x, sigma^2,alpha, type); 
tt=(n-1)*s2/sigma^2;
fprintf('The value of the test statistc tt is %f (given by ttest %f)\n',tt,vstat.chisqstat)
RR_Vartest(alpha,n-1,type);
if h==1
    fprintf('The null hypothesis is rejected (tt in RR)\n')
else
    fprintf('The null hypothesis is NOT rejected (tt not in RR)\n ')
end    
if alpha>=p 
    fprintf('The null hypothesis is rejected\n')
else
    fprintf('The null hypothesis is NOT rejected\n')
end