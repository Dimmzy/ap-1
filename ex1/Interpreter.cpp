//
// Created by dima on 11/11/2019.
//
#include <stack>
#include <queue>
#include <regex>
#include "Interpreter.h"
#include "Value.h"
#include "UMinus.h"
#include "UPlus.h"
#include "Plus.h"
#include "Minus.h"
#include "Mul.h"
#include "Div.h"
#include "Variable.h"

Expression *Interpreter::interpret(const string &str) {
  stack<Expression*> expStack;
  regex number("[0-9]+[.]*[0-9]*");
  regex binaryOp("[+*/-]");
  regex unaryOp("[@#]");
  regex variable("(_[0-9a-zA-Z]*?)|([a-zA-Z]+[0-9]*)");
  queue<string> postfix = ShuntingYard(str);
  while(!postfix.empty()) {
    string curr = postfix.front();
    if (regex_match(curr,number))
      expStack.push(new Value(stod(curr)));

    if (regex_match(curr,variable)) {
      auto it = this->varMap.find(curr);
      if (it == this->varMap.end())
        throw "Variable isn't defined";
      double val = stod(this->varMap.find(curr)->second);
      expStack.push(new Variable(curr,val));
    }


    if (regex_match(curr,unaryOp)) {
      Expression *op = expStack.top();
      expStack.pop();
      if (curr == "@")
        expStack.push(new UMinus(op));
      else
        expStack.push(new UPlus(op));
    }

    if (regex_match(curr,binaryOp)) {
      Expression *op1 = expStack.top();
      expStack.pop();
      Expression *op2 = expStack.top();
      expStack.pop();
      if (curr == "-")
        expStack.push(new Minus(op1,op2));
      else if (curr == "+")
        expStack.push(new Plus(op1,op2));
      else if (curr == "*")
        expStack.push(new Mul(op1,op2));
      else if (curr == "/")
        expStack.push(new Div(op1,op2));
    }
    postfix.pop();
  }
  return expStack.top();
}

void Interpreter::setVariables(const string &vars) {
  vector<string> variableTokens = tokenize(vars,';');
  // Checks for invalid input (number before variable name)
  for (size_t i = 0; i < variableTokens.size(); i += 2) {
    if (isdigit(variableTokens[i][0]))
      throw ("Invalid variable input!");
  }

  // Map variables and their integer values to the varMap variable.
  for (auto & variableToken : variableTokens) {
    vector<string> tokenized = tokenize(variableToken,'=');
    for(auto & var : this->varMap) {
      if (var.first == tokenized[0]) {
        var.second = tokenized[1];
        continue;
      }
    }
    this->varMap.insert(pair<string, string>(tokenized[0],tokenized[1]));
  }
}

queue<string> Interpreter::ShuntingYard(string str) {
  for(size_t i=0; i < str.length(); i++) {
    if (str[i] == '-' || str[i] == '+') {
      if(i == 0 || str[i-1] == '/' || str[i-1] == '*' || str[i-1] == '/' || str[i-1] == '+' || str[i-1] == '(') {
        switch(str[i]){
          case('-'):
            str[i] = '@';
            break;
          case('+'):
            str[i] = '#';
            break;
        }
      }
    }
  }
  queue<string> postfix;
  stack<string> s;
  regex var("(_[0-9a-zA-Z]*?)|([a-zA-Z]+[0-9]*)");
  int i(0);
  while (i < str.length()) {
    string tempStr(1, str[i]);
    if (isdigit(str[i]) || regex_match(tempStr,var)) {
      string tempNum;
      while ((isdigit(str[i]) || str[i] == '.' || regex_match(tempStr,var)) && i < str.length()) {
        tempNum.push_back(str[i]);
        i++;
        tempStr=str[i];
      }
      postfix.push(tempNum);
    } else if (isOperator(tempStr)) {
      if (tempStr == "@" || tempStr == "#") {
        while (!s.empty() && precedence(s.top()) > precedence(tempStr)) {
          postfix.push(s.top());
          s.pop();
        }
      }
      while (!s.empty() && precedence(s.top()) >= precedence(tempStr)) {
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
  if (s == "@" || s == "#")
    return 3;
  if (s == "*" || s == "/")
    return 2;
  if (s == "+" || s == "-")
    return 1;
  else
    return 0;
}

bool Interpreter::isOperator(const string &s) {
  return (s == "+" || s == "-" || s == "*" || s == "/" || s == "@" || s == "#");
}

vector<string> Interpreter::tokenize(const string &str,const char delimiter) {
  vector<string> tokens;
  string currentToken;
  istringstream tokenStream(str);
  while(getline(tokenStream, currentToken, delimiter))
    tokens.push_back(currentToken);
  return tokens;
}


