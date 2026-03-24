#include <iostream>
#include <stdlib.h>
#include <print>
#include <string>

struct HeapMemory {
  void* memory;
  HeapMemory(const HeapMemory&) = delete;
  HeapMemory(size_t size) : memory(malloc(size)) {}
  ~HeapMemory() { free(memory); }
};

struct Human {
  std::string name;
  int age;
};

struct Pair {
  int x;
  int y;
};


  // pointer is always a 64-bit integer value
void print_pair(Pair* p) {
  std::println("{} {}", p->x, p->y);
}

void print_by_ref(Pair& p) {
  std::println("{} {}", p.x, p.y);
}


void printHelloNTimes(int times) {
    for (int i = 0; i < times; ++i) {
        std::print("Hello COFFEE from the Igloo");
    }
}

void printHelloNTimesRecursive(int times) {
    if (times == 0) { return; }
    std::print("Hello, world ");
    printHelloNTimesRecursive(times - 1);
}

int main() {
    printHelloNTimes(100000);
    std::println("COFFEE");
    printHelloNTimesRecursive(100000);
    // here
    std::println("Done brewing Coffee");
    int array[3]; // on the stack
    // if the size is dynamic, we would need to allocate it.

    // created an array on the heap
    int* address = static_cast<int*>(malloc(5 * sizeof(int)));
    address[0] = 1;
    address[1] = 2;
    address[2] = 4;
    address[3] = 8;
    address[4] = 16;

      // because we have allocated on the heap, we NEED to free that memeory - otherwise we will have a memeory leak. 

    // freed automatically - this is the fundamental principle for smart pointers
    HeapMemory mem(5 * sizeof(int));
    int* temp = (int*) mem.memory;

    temp[0] = 1;
    temp[1] = 2;
    temp[2] = 4;
    temp[3] = 8;
    temp[4] = 16;

    for (int i = 0; i < 5; ++i) {
        std::println("temp: {}\naddress: {}\nAddress in memory for temp: {}", temp[i], address[i], (long) temp);
    } 

    free(address);

    std::shared_ptr<int> shared_integer = std::make_shared<int>(10);


    Pair p{1, 2};
    print_pair(&p);
    print_by_ref(p);

    return 0;

} 

