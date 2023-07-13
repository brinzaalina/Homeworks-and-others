function Lvals = Lagrange(nodes, func, vals)
    nodeSize = length(nodes);
    wiVals = zeros(1, nodeSize);
    valSize = length(vals);
    Lvals = zeros(1, valSize);
    for index = 1:valSize
        s1 = 0;
        s2 = 0;
        for i = 1:nodeSize
            wiVals(i) = Wi(nodes, i);
            s1 = s1 + wiVals(i) * func(i) / (vals(index) - nodes(i));
            s2 = s2 + wiVals(i) / (vals(index) - nodes(i));
        end
        Lvals(index) = s1 / s2;
    end
end