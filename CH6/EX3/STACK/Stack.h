#ifndef _Stack_h_
#define _Stack_h_

class Stack {

 public:
  
  // Constructor:
  Stack();

  // Copy Constructor
  Stack(const Stack& b);

  // Decstructor:
  ~Stack();

  // Assignment Operator
  Stack & operator= (const Stack & stack);

  // Push:
  void push(int i);

  // Pop:
  int pop();

  // How big is the stack?
  unsigned int size() const;

  // Print (to std::cout) 
  void print() const;

  // Test if the stack is empty
  bool isEmpty() const;

  Stack operator+(const Stack & b);

 private:

  const int increment=10;
  int _size=1024;

  unsigned int       _count;            // Actual length of stack.
  int                *_data;  // An array to store data.

};



#endif
