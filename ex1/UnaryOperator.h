//
// Created by dima on 11/11/2019.
//

#ifndef EX1__UNARYOPERATOR_H_
#define EX1__UNARYOPERATOR_H_
#include "Expression.h"

class UnaryOperator : public Expression {
 protected:
  Expression* exp;
 public:
  explicit UnaryOperator(Expression* exp);
  virtual ~UnaryOperator() = default;
};

#endif //EX1__UNARYOPERATOR_H_
