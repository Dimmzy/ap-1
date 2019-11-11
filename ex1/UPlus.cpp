//
// Created by dima on 11/11/2019.
//

#include "UPlus.h"
UPlus::UPlus(Expression *exp) : UnaryOperator(exp) {

}
double UPlus::calculate() {
  return UnaryOperator::exp->calculate();
}
UPlus::~UPlus() {
  delete(UnaryOperator::exp);
}
