function RR_Ftest(alpha,n1,n2,type)

 switch type
     case -1
         l=-Inf;
         r=icdf('f',alpha,n1,n2);
         fprintf('The rejection region, RR, is (%f, %f)\n',l,r)
     case 0
         r=icdf('f',1-alpha/2,n1,n2);
         l=icdf('f',alpha/2,n1,n2);
         fprintf('The rejection region, RR, is (%f,%f)U(%f, %f)\n',-Inf,l,r,Inf)
     case 1
         l=icdf('f',1-alpha,n1,n2);
         r=Inf;
         fprintf('The rejection region, RR, is (%f, %f)\n',l,r)
 end