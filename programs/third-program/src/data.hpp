#pragma once
struct Point {
    int x;
    int y;
};

struct Data {
  Point point;
  // what would be the smart way to reference the struct?
};

inline int add(int a, int b) { return a + b;}
