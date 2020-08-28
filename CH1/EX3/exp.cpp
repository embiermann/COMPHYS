//
// Emily Biermann
// Ch1 EX4
// exp by taylor series expansion
//

#include <iostream>
#include <cmath>
#include <sstream>
#include <math.h> // pow

int main(int argc, char **argv)
{
  float x;
  float expon; 
  float factorial;

  for(int i; i<=argc; i++){
    expon=1.0;
    factorial = 1.0;
    std::istringstream stream(argv[i]);
    
    if (stream >> x) {
      for(int n=1; n<100; n++){
        factorial *= n;
        expon = expon + pow(x,n)/factorial;
      }
    
      std::cout<<expon<<std::endl;
    }
    else{
      std::cout<<"Invalid Input"<<std::endl;
    }
  }
  return 0;
}
