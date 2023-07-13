function NI = newton(x, f, vals)
    n = length(x) - 1;
    dd = divided_diff(x, f);
    l = length(vals);
    P = ones(1, l);
    s = dd(1, 1) * ones(1, l);
    for j = 1 : l
        for i = 1 : n
            P(j) = P(j) * (vals(j) - x(i));
            s(j) = s(j) + P(j) * dd(1, i + 1);
        end
    end
    NI = s;
end