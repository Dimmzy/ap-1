//
// Created by dima on 11/11/2019.
//

#include "Minus.h"
Minus::Minus(Expression *right, Expression *left) : BinaryOperator(left, right) {

}
double Minus::calculate() {
  return BinaryOperator::right->calculate() - BinaryOperator::left->calculate();
}
Minus::~Minus() {
  delete(BinaryOperator::left);
  delete(BinaryOperator::right);
}
