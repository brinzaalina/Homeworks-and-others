//
// Created by selen on 19/06/2021.
//

#include "classes.h"

Constant::Constant(double value) {
    this->value = value;
}

double Constant::evaluate() {
    return this->value;
}

UnaryExpression::UnaryExpression(Expression *right) {
    this->right = right;
}

double UnaryExpression::evaluate() {
    return this->right->evaluate();
}

Negate::Negate(Expression *expression) : UnaryExpression(expression) {
}

double Negate::evaluate() {
    return -this->right->evaluate();
}

BinaryExpression::BinaryExpression(Expression *right, Expression *left): UnaryExpression(right) {
    this->left = left;
}

Adder::Adder(Expression *right, Expression *left) : BinaryExpression(right, left) {
}

double Adder::evaluate() {
    return this->right->evaluate() + this->left->evaluate();
}

Subtracter::Subtracter(Expression *right, Expression *left) : BinaryExpression(right, left) {
}

double Subtracter::evaluate() {
    return this->right->evaluate() - this->left->evaluate();
}

void MathHomework::addExpression(Expression *expression) {
    this->elements.push_back(expression);
}

std::list<double> MathHomework::getResults() {
    std::list<double> result;
    for (auto expression: this->elements) {
        result.push_back(expression->evaluate());
    }
    return result;
}
