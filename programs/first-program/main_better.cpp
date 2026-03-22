#include <iostream>

// default structs are public baby

struct Example {
  int a;
  int b;
  int calc(int c, int d){return c + d;};// need a body in this bitch
};


// interface
struct Foo {
  virtual int bar(int, int) = 0; // virtual means, please override me, = 0 means abstract
};

// :oooooo 
struct Bar : Foo {
  int bar(int a, int b) override {
    return a + b;
  }
};


int calc(Foo& f) {
  return f.bar(1, 2);
}

int main() {
  Example e{
    2, 3
  };

  
  Bar b; // barbie lol
  int overall_value = calc(b);



  int value = e.calc(e.a, e.b);

  std::cout << value << " This is the first example, " << std::endl;
  std::cout << overall_value << " This is soooooo much better, got me hard" << std::endl; // "" = const char* !string

  return 0;
}
