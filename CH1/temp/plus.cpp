//
// Emily Biermann
//

#include<iostream>
#include<sstream>

int main(int argc, char ** argv){
  int int_1;
  int int_2;

  std::stringstream(argv[1])>>int_1;
  std::stringstream(argv[2])>>int_2;
  std::cout<<int_1<<" + "<<int_2<<" = "<<int_1+int_2;
  std::cout << std::endl;
		   
  
  return 0;
}
