//
// Created by dima on 11/11/2019.
//
#include <stack>
#include <queue>
#include <sstream>
#include "Interpreter.h"

Expression *Interpreter::interpret(string &str) {

}

void Interpreter::setVariables(string &vars) {

}

queue<string> Interpreter::ShuntingYard(string str) {
  queue<string> postfix;
  stack<string> s;
  int i(0);
  while (i < str.length()) {
    string tempStr(1, str[i]);
    if (isdigit(str[i])) {
      string tempNum;
      while ((isdigit(str[i]) || str[i] == '.') && i < str.length()) {
        tempNum.push_back(str[i]);
        i++;
      }
      postfix.push(tempNum);
    } else if (isOperator(tempStr)) {
      while (!s.empty() && precedence(s.top()) > precedence(tempStr)) {
        postfix.push(s.top());
        s.pop();
      }
      s.push(tempStr);
      i++;
    } else if (tempStr == "(") {
      s.push(tempStr);
      i++;
    } else if (tempStr == ")") {
      while (!s.empty() && s.top() != "(") {
        postfix.push(s.top());
        s.pop();
      }
      s.pop();
      i++;
    }
  }
  while (!s.empty()) {
    postfix.push(s.top());
    s.pop();
  }
  return postfix;
}

int Interpreter::precedence(const string &s) {
  if (s == "*" || s == "/")
    return 2;
  if (s == "+" || s == "-")
    return 1;
  else
    return 0;
}

bool Interpreter::isOperator(const string &s) {
  return (s == "+" || s == "-" || s == "*" || s == "/");
}

