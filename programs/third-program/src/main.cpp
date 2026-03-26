#include <print>
#include "data.hpp"

int main() {
  std::println("Hello, world!");
  int value = add(10, 20);
  Data d = {
    { 10, 20 }
  };

  std::println("Combined point values {}\n", add(d.point.x, d.point.y));
  
  return 0;
}
