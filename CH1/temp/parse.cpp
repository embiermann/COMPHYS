#include "plus.h"

inputs parse(int argc, char ** argv){
  inputs x;
  
  std::stringstream(argv[1])>>x.in1;
  std::stringstream(argv[2])>>x.in2;

  return x;
		    
}
