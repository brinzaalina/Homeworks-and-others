function [li,ri]=ConfIntDifMeanNotVarEq(x1,x2,alpha)

n1=length(x1);
n2=length(x2);
n=n1+n2-2;

mx1=mean(x1);
mx2=mean(x2);
vx1=var(x1);
vx2=var(x2);

t=icdf('t',1-alpha/2,n);
rad=sqrt(1/n1+1/n2);
sp=sqrt(((n1-1)*vx1+(n2-1)*vx2)/n);

li=mx1-mx2-t*sp*rad;
ri=mx1-mx2+t*sp*rad;