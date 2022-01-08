function RR_Ttest(alpha,n,type)

 switch type
     case -1
         l=-Inf;
         r=icdf('t',alpha,n);
         fprintf('The rejection region, RR, is (%f, %f)\n',l,r)
     case 0
         r=icdf('t',1-alpha/2,n);
         l=-r;
         %l=icdf('t',alpha/2,n-1);
         fprintf('The rejection region, RR, is (%f,%f)U(%f, %f)\n',-Inf,l,r,Inf)
     case 1
         l=icdf('t',1-alpha,n);
         r=Inf;
         fprintf('The rejection region, RR, is (%f, %f)\n',l,r)
 end