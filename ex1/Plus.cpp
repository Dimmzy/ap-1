//
// Created by dima on 11/11/2019.
//

#include "Plus.h"
Plus::Plus(Expression *right, Expression *left) : BinaryOperator(right, left) {
}
double Plus::calculate() {
  return BinaryOperator::right->calculate() + BinaryOperator::left->calculate();
}
Plus::~Plus() {
  delete(BinaryOperator::left);
  delete(BinaryOperator::right);
}
