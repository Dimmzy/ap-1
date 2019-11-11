//
// Created by dima on 11/11/2019.
//

#include "Mul.h"
Mul::Mul(Expression *right, Expression *left) : BinaryOperator(right, left) {

}
double Mul::calculate() {
  return BinaryOperator::right->calculate() * BinaryOperator::left->calculate();
}
Mul::~Mul() {
  delete(BinaryOperator::left);
  delete(BinaryOperator::right);
}
