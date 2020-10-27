#include "STACK/Stack.h"
#include <iostream>
#include <stdexcept>
using namespace std;

// The constructor is called every time an object is created.
// This insures that the object starts from a well defined state
// ... without requiring further initialization from the client.


// unimplemented!
Stack::Stack():_count(0),_data(new int [_size]){
  // ==> Insert code here:
  std::cout<<"Hello from the constructor"<<std::endl;
}

// Copy Constructor
Stack::Stack(const Stack& stack):_count(stack._count),_size(stack._size),increment(stack.increment){
  std::cout<<"Hello from the copy constructor"<<std::endl;
  _data=new int[stack._size];
  for(int i=0;i<_count;i++){
    _data[i]=stack._data[i];
  }
}

// Destructor
Stack::~Stack(){
  std::cout<<"Farewell"<<std::endl;
  delete [] _data;
}

// Assignment Operator
Stack& Stack::operator= (const Stack & stack){
  std::cout<<"Hello from the assignment operator"<<std::endl;

  if (this == &stack) return *this;
  
  int *newmemory=new int[stack._size];
  _count=stack._count;
  _size=stack._size;
  for(int i=0;i<_count;i++){
    newmemory[i]=stack._data[i];
  }

  delete [] _data;
  _data=newmemory;
  
  return *this;
}

// The push function increases the length of the stack by one element
// add the value to the end of the stack.  

// unimplemented!  
void Stack::push(int i) {
  // ==> insert code here
  if(_count==_size){
    _size += increment;
    int *newLocation=new int [_size];
    for(int i=0;i<_count;i++){
      newLocation[i]=_data[i];
    }
    delete [] _data;
    _data=newLocation;
  }
  _data[_count] = i;
  _count++;
}

// The pop function decreases the length of the stack by one element, 
// and returns the value that is popped off

// unimplemented!  
int Stack::pop(){
  //  ==> Change the following line to something sensible...
  _count--;
  return _data[--_count];
}

// The size function returns the size of the stack. The stack does
// not change so this function is "const".

// unimplemented!  
unsigned int Stack::size() const {
  //  ==> Change the following line to something sensible...
  return _count;
}

// The print function dumps the entire stack to std::cout, in a 
// human-readable format.  The stack does not change, so this function
// is "const"

// unimplemented!  
void Stack::print() const {
  // ==> insert code here
  for(int i=0; i<_count; i++){
    std::cout<<_data[i]<<std::endl;
  }
}

// The isEmpty() query function returns true or false, depending on 
// whether the stack is empty (length 0).  The stack does not change,
// so this function is "const"

// unimplemented!  
bool Stack::isEmpty() const {
  // Change the following line to something sensible
  return _count==0;
}

Stack Stack::operator+(const Stack & b){
  Stack c=(*this);
  for (int i=0;i<b._count;i++) c.push(b._data[i]);
  return c;
}
