#include <iostream>
#include <string>
#include <cstdlib>


void print(std::string message) {
  std::cout << message << std::endl;
}


std::vector<std::string> secretMessages = {
  "secret",
  "Message",
  "Message",
  "Message",
  "Message",
  "Message",
  "Message",
  "Message",
  "Message",
  "Message",
};

std::vector<std::string> normalMessages = {
  "Hello",
  "I",
  "Love",
  "You",
  "But",
  "You",
  "Smell",
  "Like",
  "Dooky",
  "",
};


void printSomethingFun(int index, int value) {

  switch (index) {
    case 0: {
      if (value >=18) {
        print(secretMessages[index]);
        break;
      } else {
        print(normalMessages[index]);
        break;
      }
    }
    case 1: {
      if (value >= 22) {
        print(secretMessages[index]);
        break;
      } else {
        print(normalMessages[index]);
        break;
      }
    }
    case 2: std::cout << "I" << std::endl; break;
    case 3: std::cout << "Love" << std::endl; break;
    case 4: std::cout << "You" << std::endl; break;
    case 5: std::cout << "But" << std::endl; break;
    case 6: std::cout << "You" << std::endl; break;
    case 7: std::cout << "Smell" << std::endl; break;
    case 8: std::cout << "Like" << std::endl; break;
    case 9: std::cout << "Shit." << std::endl; break;
    default: std::cout << "default" << std::endl;
  }
}


// yo wtf... that number is the same across all programs? Waiiititiitititiitiitit
int main() {
  int n = rand(); // 16807
  if (n > 22) {
    std::cout << "Shit you made it :)" << std::endl;
  } else {
    std::cout << "Get bent kid." << std::endl;
  }
  //std::cout << n << std::endl;


  std::vector<int> v = {56, 69, 21, 82, 15, 2, 1, 3, 9, 5};


  for (int i = 0; i < v.size(); ++i) {
    /**
    std::cout << v[i] << std::endl; // wtf... it's not 0 bvased? lmao
    std::cout << i << std::endl;
    **/


    printSomethingFun(i, v[i]);

  }


  return 0;
}
