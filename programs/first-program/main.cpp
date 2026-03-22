#include <iostream>

/**
 * Author: { @Override } -> 20260317 @23:33 
 **/
class HelloWorld {
  public:
    void sayHello() {
      std::cout << "Hello World!" << std::endl;
    }
};

// or can be functional like this

void sayHello() { std::cout << "Hello World!" << std::endl; }

int main() {
  HelloWorld helloWorld;
  helloWorld.sayHello();

  // just using function (I like better)
  sayHello();

  return 0;
}
