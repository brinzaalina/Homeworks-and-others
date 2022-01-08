function [li,ri]=ConfIntVarRation(x1,x2,alpha)

n1=length(x1);
n2=length(x2);

vx1=var(x1);
vx2=var(x2);

f1=finv(1-alpha/2,n1-1,n2-1);
f2=finv(alpha/2,n1-1,n2-1);

rap=vx1/vx2;

li=rap/f1;
ri=rap/f2;