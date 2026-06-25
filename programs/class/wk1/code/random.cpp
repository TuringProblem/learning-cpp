#include <iostream>
#include <cstdlib>



// okay srand()

int main() {
  // 16807
  int n = rand(); // why is this the same number every re-compile?

  srand(time(0));
  std::cout << "Your random number: " << n << std::endl;
  std::cout << "Random Max: " << RAND_MAX << std::endl;
  std::cout << "Real Random generated: [1] " << (rand() % 10) << std::endl;
  std::cout << "Real Random generated: [2] " << (rand() % 10) << std::endl;
  std::cout << "Real Random generated: [3] " << (rand() % 10) << std::endl;
  return 0;
}
