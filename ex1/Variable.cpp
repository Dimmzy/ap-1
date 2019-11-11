//
// Created by dima on 11/11/2019.
//

#include "Variable.h"

#include <utility>

Variable::Variable(std::string name, double value) {
  this->name = std::move(name);
  this->value = value;
}
Variable &Variable::operator++() {
  this->value++;
  return *this;
}
Variable &Variable::operator--() {
  this->value--;
  return *this;
}
Variable &Variable::operator+=(double value) {
  this->value = this->value += value;
  return *this;
}
Variable &Variable::operator-=(double value) {
  this->value = this->value -= value;
  return *this;
}
Variable &Variable::operator++(int value) {
  this->value++;
  return *this;
}
Variable &Variable::operator--(int value) {
  this->value--;
  return *this;
}

double Variable::calculate() {
  return this->value;
}
