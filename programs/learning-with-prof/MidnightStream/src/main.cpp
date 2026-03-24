#include <iostream>
#include <print>

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
    return 0;
} 
// can you run this, I don't have perms :o - I want to see if this workd}ss