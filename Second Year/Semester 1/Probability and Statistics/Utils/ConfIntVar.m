function [li,ri]=ConfIntVar(x,alpha)

n=length(x);
q1=icdf('chi2',1-alpha/2,n-1);
q2=icdf('chi2',alpha/2,n-1);
v=var(x);

li=(n-1)*v/q1;
ri=(n-1)*v/q2;