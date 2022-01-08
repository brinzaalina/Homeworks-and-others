function [li,ri]=ConfIntDifMeanNotVarDif(x1,x2,alpha)

n1=length(x1);
n2=length(x2);

mx1=mean(x1);
mx2=mean(x2);
vx1=var(x1);
vx2=var(x2);

c=(vx1/n1)/(vx1/n1+vx2/n2);
n=1/(c^2/(n1-1)+(1-c)^2/(n2-1));

t=icdf('t',1-alpha/2,n);
rad=sqrt(vx1/n1+vx2/n2);


li=mx1-mx2-t*rad;
ri=mx1-mx2+t*rad;