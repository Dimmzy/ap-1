//
// Created by dima on 11/11/2019.
//

#include "UMinus.h"

UMinus::UMinus(Expression *exp) : UnaryOperator(exp) {

}
double UMinus::calculate() {
  return -(UnaryOperator::exp->calculate());
}
UMinus::~UMinus() {
  delete(UnaryOperator::exp);
}
