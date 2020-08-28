//
// Emily Biermann
// plus main program
//

#include "plus.h"

int main(int argc, char ** argv){
  inputs x;
  int sum;
  
  x = parse(argc, argv);
  sum = add(x);
  print(x, sum);
  return 0;
}

