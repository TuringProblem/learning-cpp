#pragma once
#include <print>

// x or y due to being a union
union MyUnion {
  int x; 
  float y;
};

inline void use() {
  MyUnion u;
  int my_value = u.x = 10;
  std::println("x: {}", my_value);
  float another_value = u.y = 10.69;
  std::println("y: {}", another_value); // this is a Language extension
}
