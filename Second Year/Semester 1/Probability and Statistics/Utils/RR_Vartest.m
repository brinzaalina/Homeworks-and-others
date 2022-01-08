function RR_Vartest(alpha,n,type)

 switch type
     case -1
         l=-Inf;
         r=icdf('chi2',alpha,n);
         fprintf('The rejection region, RR, is (%f, %f)\n',l,r)
     case 0
         r=icdf('chi2',1-alpha/2,n);
         l=icdf('chi2',alpha/2,n);
         fprintf('The rejection region, RR, is (%f,%f)U(%f, %f)\n',-Inf,l,r,Inf)
     case 1
         l=icdf('chi2',1-alpha,n);
         r=Inf;
         fprintf('The rejection region, RR, is (%f, %f)\n',l,r)
 end