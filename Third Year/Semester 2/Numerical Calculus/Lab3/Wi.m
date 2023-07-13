function retval = Wi(x, i)
    size = length(x);
    u = 1;
    for j = 1:size
        if i ~= j
            u = u * (x(i) - x(j));
        end
    end
    retval = 1 / u;
end