#include <iostream>

void print_array_two(std::array<int, 10> arr, size_t size) {
  for (size_t i = 0; i < size; i++) {
    std::cout << "Print std::array<int, 10>: " << arr[i] << "\n";
  }
}

void print_array(int* ptr_to_array, size_t size) {
  for (size_t i = 0; i < size; i++) {
    std::cout << "Print array: " << ptr_to_array[i] << "\n";
  }
}

void find_five(int* ptr_to_array, size_t size) {
  for (size_t i = 0; i < size; i++) {
    if (i == 5) { std::cout << "Found: " << i << " at index: " << ptr_to_array[i] << "\n"; }
  }
}

int find_five_recursive(int* ptr_to_array, size_t size) {
  if (size == 0) { return -1; }

  if (ptr_to_array[0] == 5) { return 0; }

  return find_five_recursive(ptr_to_array + 1, size - 1);
}


struct Example { 
  std::array<int, 10> arr;
  print_arr(std::array<int, 10> arr, size_t size){
    for (size_t i = 0; i < size; i++) {
      std::cout << "Print std::array<int, 10>: " << arr[i] << "\n";
    }
  };
};

int main() {
  std::array<int, 10> arr = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
  int array[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
  // implicit conversion
  print_array(array, 10); // passing pointer to first element
  print_array_two(arr, 10); 
  std::cout << find_five(array, 10) << "\n";


  Example e = {
    { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }
  };

  e.print_arr(e.arr, 10);

  return 0;
}
