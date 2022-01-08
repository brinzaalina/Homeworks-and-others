function [li,ri]=ConfIntMeanNotVar(x,alpha)

n=length(x);
t=icdf('t',1-alpha/2,n-1);
mx=mean(x);
s=std(x);

li=mx-s/sqrt(n)*t;
ri=mx+s/sqrt(n)*t;