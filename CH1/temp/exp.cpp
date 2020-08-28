#include <iostream>
#include <cmath>
#include <sstream>

int main(int argc, char **argv)
{
  int x;

  for(int i=1;i<=argc;i++){
    std::istringstream stream(argv[i]);
    if (stream >> x) {
      std::cout<<exp(x)<<std::endl;
    }
    else{
      std::cout<<"Invalid Input"<<std::endl;
    }
  }
  
  return 0;
}
