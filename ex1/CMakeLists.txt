cmake_minimum_required(VERSION 3.15)
project(ex1)

set(CMAKE_CXX_STANDARD 11)

add_executable(ex1 ex1.cpp ex1.h Variable.cpp Variable.h Value.cpp Value.h UnaryOperator.cpp UnaryOperator.h UPlus.cpp UPlus.h BinaryOperator.cpp BinaryOperator.h UMinus.cpp UMinus.h Plus.cpp Plus.h Minus.cpp Minus.h Mul.cpp Mul.h Div.cpp Div.h mainTester.cpp Interpreter.cpp Interpreter.h)