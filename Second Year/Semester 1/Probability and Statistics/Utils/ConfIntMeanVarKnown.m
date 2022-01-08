function [li,ri]=ConfIntMeanVarKnown(x,alpha,sigma)

n=length(x);
z=icdf('norm',1-alpha/2,0,1);
mx=mean(x);

li=mx-sigma/sqrt(n)*z;
ri=mx+sigma/sqrt(n)*z;