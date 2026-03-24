#include <iostream>
#include <stdlib.h>
#include <print>

struct HeapMemory {
  void* memory;
  HeapMemory(size_t size) : memory(malloc(size)) {}
  ~HeapMemory() { free(memory); }
};


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
    free(address);

    // freed automatically - this is the fundamental principle for smart pointers
    HeapMemory mem(5 * sizeof(int));

    return 0;

} 

