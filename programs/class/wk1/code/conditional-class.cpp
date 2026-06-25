#include <iostream>

void ifSituations(int expr) {
  if (expr < 0) {
    std::cout << "Negative\n";
  } else {
    std::cout << "Positive\n";
  }
}


void runCases(int expr) {
  switch(expr) {
    case 1: std::cout << "One\n"; break;
    case 2: std::cout << "Two\n"; break;
    case 3: std::cout << "Three\n"; break;
    default: std::cout << "Zerno\n";
  }
}
int main() {

  std::cout << "Enter a Number: ";
  int n;
  std::cin >> n;
  std::cin.ignore(256, '\n');

  std::cout << n << " is the number you entered\n";
  n = n + 1;

  std::cout << n << " Is the number added by 1\n";

  n = -n; 


  std::cout << n << " Is the negation of the number\n";



  n += n; 
  std::cout << n << " Is the number added by 1\n";
  n = -n;
  std::cout << n << " Is the negation of the number\n";


  // unary operators
  // difference between prefix and postfix -> postfix returns the value that n was before and prefix return the value after its been incremented
  n++;
  std::cout << n << " returning the old value of 1\n";
  ++n;
  std::cout << n << " Returning the new value of 1\n";


  // comparison operators
  //
  n > 10 ? std::cout << "n is greater than 10\n" : std::cout << "n is less than 10\n";

  bool b = n < 10; // false = 0, true = 1

  std::cout << b << std::endl;

  ifSituations(n);


  // using a lambda fuction where everythign is by reference
  auto isEven = [&](int x) { return x % 2 == 0; };


  isEven(n) ? std::cout << n << " is even\n" : std::cout << n << " is odd\n";
  
  // switch statement has follow through - meaning if you don't do break; after something then it will proceed down the next case.
  runCases(n);

  return 0;
}
