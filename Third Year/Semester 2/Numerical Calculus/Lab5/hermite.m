function sol = hermite(nodes, func, fprime, point)
    no_nodes = length(nodes);
    new_nodes = [];
    new_func = [];
    for i = 1 : no_nodes
        new_nodes = [new_nodes nodes(i) nodes(i)];
        new_func = [new_func func(i) func(i)];
    end
    nodes = new_nodes;
    func = new_func;
    no_nodes = length(nodes);
    table = [nodes ; func];
    new_table = [];
    for j = 1 : no_nodes - 1
        if mod(j, 2) == 1
            new_table = [new_table fprime((j + 1)/2)];
        else
            new_table = [new_table (table(2, j + 1) - table(2, j)) / (table(1, j+1) - table(1, j))];
        end
    end
    table = [table; new_table 0];
    for i = 3 : no_nodes
        new_table = [];
        for j = 1 : no_nodes - i + 1
            new_table = [new_table (table(i, j + 1) - table(i, j)) / (table(1, j + i -1) - table(1, j))];
        end
        new_table = [new_table zeros(1, i - 1)];
        table = [table ; new_table];
    end
    table = table';
    
    prod = 1;
    sol = 0;
    for i = 1 : no_nodes
        sol = sol + prod * table(1, i + 1);
        prod = prod * (point - nodes(i));
    end
end