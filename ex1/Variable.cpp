

#include "Variable.h"

#include <utility>

Variable::Variable(std::string name, double value) {
  this->varname = std::move(name);
  this->varvalue = value;
}
Variable &Variable::operator++() {
  this->varvalue++;
  return *this;
}
Variable &Variable::operator--() {
  this->varvalue--;
  return *this;
}
Variable &Variable::operator+=(double value) {
  this->varvalue += value;
  return *this;
}
Variable &Variable::operator-=(double value) {
  this->varvalue -= value;
  return *this;
}
Variable &Variable::operator++(int) {
  this->varvalue++;
  return *this;
}
Variable &Variable::operator--(int) {
  this->varvalue--;
  return *this;
}

double Variable::calculate() {
  return this->varvalue;
}
