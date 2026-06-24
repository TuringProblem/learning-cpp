#include <iostream>
#include "Node.hpp"

class LinkedList {
  private:
    Node* head;
    Node* tail;
    int len;

  public:
    LinkedList(int value) {
      Node* newNode = new Node(value);
      head = newNode;
      tail = newNode;
      len = 1;
    }
    void printList() {
      Node* current = head;
      while (current != nullptr) {
        std::cout << current->value << "\n";
        current = current->next;
      }
    }

    void add(int value) {
      Node* newNode = new Node(value);
      tail->next = newNode;
      tail = newNode;
      len++;
    }

    Node* getHead() { return head; }
    Node* getTail() { return tail; }
    int getLen() { return len; }
    
    


};
int main() {

  LinkedList* list = new LinkedList(1);
  list->printList();
  list->add(2);
  list->add(5);
  list->add(69);
  list->add(12);
  list->printList();

  std::cout << "Head value: " << list->getHead()->value << "\n";
  std::cout << "Tail value: " << list->getTail()->value << "\n";



  return 0;
};
