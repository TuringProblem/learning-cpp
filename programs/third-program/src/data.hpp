#pragma once
#include <iostream>
#include <print>

struct Point {
    int x;
    int y;
};

// what would be the smart way to reference the struct?
struct Data {
  Point point;
};

inline int add(int a, int b) { return a + b;}

inline void main_screen() {
  std::println("Hello, Please enter two numbers:  !");
  char input[10];
  // expected input for two numbers is {10, 20} | {10 20} - need take input as a token of chars, and look for either a space or ","


}

