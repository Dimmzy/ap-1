//
// Created by dima on 11/11/2019.
//

#ifndef EX1__INTERPRETER_H_
#define EX1__INTERPRETER_H_

#include <string>
#include "Expression.h"
class Interpreter {
 private:

 public:
  void setVariables(string vars);
  Expression* interpret(string str);
  Interpreter() = default;
  ~Interpreter();
};

#endif //EX1__INTERPRETER_H_
