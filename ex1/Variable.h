
#ifndef EX1__VARIABLE_H_
#define EX1__VARIABLE_H_
#include <string>
#include "Expression.h"

class Variable : public Expression {
 public:
  Variable(std::string name, double value);
  Variable &operator++();
  Variable &operator--();
  Variable &operator+=(double value);
  Variable &operator-=(double value);
  Variable &operator++(int value);
  Variable &operator--(int value);
  double calculate() override;
  virtual ~Variable() = default;
 private:
  string varname;
  double varvalue;
};

#endif //EX1__VARIABLE_H_
