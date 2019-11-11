//
// Created by dima on 11/11/2019.
//

#include "Div.h"
Div::Div(Expression *right, Expression *left) : BinaryOperator(right, left) {

}
double Div::calculate() {
  // Division by zero
  if (BinaryOperator::left->calculate() == 0) {
    throw "bad input"; // fix this shit
  }
  return BinaryOperator::right->calculate() / BinaryOperator::left->calculate();
}
Div::~Div() {
  delete(BinaryOperator::left);
  delete(BinaryOperator::right);
}

