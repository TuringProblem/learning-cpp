#include <iostream>
#include <string>

// decent if it's one line or something - but for multiple inputs, it's not good
int readInt() {
  int n;
  std::cout << "Enter an interger: ";
  std::cin >> n;
  return n;
}

int readInt2() {
  int n;
  std::cout << "Enter an interger: ";
  std::cin >> n;
  std::cin.ignore(256, '\n');
  return n;
}

// 
std::string readName() {
  std::string name;
  std::cout << "Enter your name: ";
  getline(std::cin, name);
  return name;
}

int main() {
  //int value = readInt();
  // this causes a PROBLEM!!! youo can do {5 andrew w} => 5 and then already does name = " andrew w"
  /**int value = readInt();
  *
  * std::string name= readName();
  */

  // solution
  int value = readInt2();
  std::string name = readName();


  std::cout << "You have entered: " << value << std::endl;
  std::cout << "You have entered: " << name << std::endl;
  std::cout << "The number you entered: " << value << std::endl;
  return 0;
}
