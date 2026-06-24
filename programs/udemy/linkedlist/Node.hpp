class Node {
  public:
    int value;
    Node* next;

    Node(int value) {
      this->value = value;
      this->next = nullptr; // I'm assuming that nullptr == assigning the value to "null" in other languages such as Java
    }
};  

