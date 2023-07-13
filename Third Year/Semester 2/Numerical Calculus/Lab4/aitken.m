function approx = aitken(x, f, val, err)
    n = length(x);
    ak = zeros(n, n);
    ak(:, 1) = f';
    for i = 1 : n
        for j = 1 : i - 1
            ak(i, j + 1) = (1/(x(i)-x(j)) * ((val - x(j)) * ak(i, j) - (val - x(i)) * ak(j, j)));
        end
        if i > 1 && abs(ak(i, i) - ak(i - 1, i - 1)) < err
            approx = ak(i, i);
            return
        end
    end
end