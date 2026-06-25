#include <iostream>
#include <vector>
#import <ranges>


int main() {
  std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  auto squared_values = v | std::views::transform([](int x) { return x * x; });

  std::cout << squared_values.size() << " is the size of the vector\n";

  std::cout << squared_values[0] << std::endl;
  for (int i : squared_values) std::cout << i << std::endl;

}
