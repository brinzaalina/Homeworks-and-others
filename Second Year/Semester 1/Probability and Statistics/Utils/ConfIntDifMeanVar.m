function [li,ri]=ConfIntDifMeanVar(x1,x2,sig1,sig2,alpha)

n1=length(x1);
n2=length(x2);

mx1=mean(x1);
mx2=mean(x2);

z=icdf('norm',1-alpha/2,0,1);
li=mx1-mx2-z*sqrt(sig1^2/n1+sig2^2/n2);
ri=mx1-mx2+z*sqrt(sig1^2/n1+sig2^2/n2);