//
// Created by selen on 19/06/2021.
//

#pragma once

#include <vector>
#include <list>

class Expression {
public:
    Expression() = default;
    virtual double evaluate() = 0;
    virtual ~Expression() = default;
};

class Constant: public Expression {
private:
    double value;
public:
    explicit Constant(double value);
    double evaluate() override;
    ~Constant() override = default;
};

class UnaryExpression: public Expression {
protected:
    Expression* right;
public:
    explicit UnaryExpression(Expression* right);
    double evaluate() override;
    ~UnaryExpression() override { delete right; }
};

class Negate: public UnaryExpression {
public:
    explicit Negate(Expression* expression);
    double evaluate() override;
};

class BinaryExpression: public UnaryExpression {
protected:
    Expression* left;
public:
    BinaryExpression(Expression* right, Expression* left);
    double evaluate() override = 0;
    ~BinaryExpression() override { delete right; delete left;}
};

class Adder: public BinaryExpression {
public:
    Adder(Expression* right, Expression* left);
    double evaluate() override;
};

class Subtracter: public BinaryExpression {
public:
    Subtracter(Expression* right, Expression* left);
    double evaluate() override;
};

class MathHomework {
private:
    std::vector<Expression*> elements;
public:
    MathHomework() = default;
    void addExpression(Expression* expression);
    std::list<double> getResults();
    ~MathHomework() = default;
};