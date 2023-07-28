//
// Created by selen on 19/06/2021.
//

#include <list>
#include <iostream>
#include "classes.h"

void first() {
    ///-5+(9-3)
    Expression* c = new Constant(5);
    Expression* n = new Negate(c);
    Expression* c1 = new Constant(9);
    Expression* c2 = new Constant(3);
    Expression* sub = new Subtracter(c1, c2);
    Expression* add = new Adder(n, sub);
    MathHomework m;
    m.addExpression(add);
    std::list<double> r = m.getResults();
    for(auto & res: r)
       std::cout<<res<<"\n";
}

void second() {
    ///-(4+2)-(-10)
    Expression* a = new Constant(4);
    Expression* b = new Constant(2);
    Expression* c= new Adder(a, b);
    Expression* d = new Negate(c);
    Expression* e = new Constant(10);
    Expression* f = new Negate(e);
    Expression* result = new Subtracter(d, f);
    MathHomework m;
    m.addExpression(result);
    std::list<double> r = m.getResults();
    for(auto & res: r)
        std::cout<<res<<"\n";
}

int main() {
    first();
    second();
    return 0;
}