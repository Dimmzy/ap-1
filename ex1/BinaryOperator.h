//
// Created by dima on 11/11/2019.
//

#ifndef EX1__BINARYOPERATOR_H_
#define EX1__BINARYOPERATOR_H_

#include "Expression.h"
class BinaryOperator : public Expression {
 protected:
  Expression* right;
  Expression* left;
 public:
  BinaryOperator(Expression* right, Expression* left);
  virtual ~BinaryOperator() = default;
};

#endif //EX1__BINARYOPERATOR_H_
