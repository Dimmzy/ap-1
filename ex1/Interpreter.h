//
// Created by dima on 11/11/2019.
//

#ifndef EX1__INTERPRETER_H_
#define EX1__INTERPRETER_H_

#include <string>
#include <map>
#include "Expression.h"
class Interpreter {
 private:
  static bool isOperator(const string& s);
  static int precedence(const string& s);
  map<string, string> varMap;
  static vector<string> tokenize(string& str, char delimiter);
 public:
  void setVariables(string& vars);
  Expression* interpret(string& str);
  Interpreter() = default;
  ~Interpreter();
  queue<string> ShuntingYard(string str);
  void replaceVariables(string &s);
};

#endif //EX1__INTERPRETER_H_
