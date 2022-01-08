function RR_Ztest(alpha,type)

 switch type
     case -1
         l=-Inf;
         r=icdf('norm',alpha,0,1);
         fprintf('The rejection region, RR, is (%f, %f)\n',l,r)
     case 0
         r=icdf('norm',1-alpha/2,0,1);
         l=-r;
         %l=icdf('norm',alpha/2,0,1);
         fprintf('The rejection region, RR, is (%f,%f)U(%f, %f)\n',-Inf,l,r,Inf)
     case 1
         l=icdf('norm',1-alpha,0,1);
         r=Inf;
         fprintf('The rejection region, RR, is (%f, %f)\n',l,r)
 end