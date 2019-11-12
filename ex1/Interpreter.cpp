//
// Created by dima on 11/11/2019.
//
#include <stack>
#include <queue>
#include <sstream>
#include <utility>
#include <regex>
#include "Interpreter.h"

Expression *Interpreter::interpret(string &str) {

}

void Interpreter::setVariables(string &vars) {
  vector<string> variableTokens = tokenize(vars,';');
  // Checks for invalid input (number before variable name)
  for (size_t i = 0; i < variableTokens.size(); i += 2) {
    if (isdigit(variableTokens[i][0]))
      throw ("Invalid variable input!");
  }
  // Map variables and their integer values to the varMap variable.
  for (auto & variableToken : variableTokens) {
    vector<string> tokenized = tokenize(variableToken,'=');
    this->varMap.insert(pair<string, string>(tokenized[0],tokenized[1]));
  }
}

queue<string> Interpreter::ShuntingYard(string inputstr) {
  // There are variables we need to replace in the expression.
  string str = std::move(inputstr);
  if (!(this->varMap.empty())) {

  }
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

vector<string> Interpreter::tokenize(string &str, char delimiter) {
  vector<string> tokens;
  string currentToken;
  istringstream tokenStream(str);
  while(getline(tokenStream, currentToken, delimiter))
    tokens.push_back(currentToken);
  return tokens;
}

void Interpreter::replaceVariables(string& s) {
  for(const auto& ele : this->varMap) {
    size_t pos = s.find(ele.first);
    while (pos != string::npos) {
      s.replace(pos, ele.first.size(), ele.second);
      pos = s.find(ele.first, pos + ele.second.size());
    }
  }
}

