#include<iostream>
#include"diag3d.h"

int main(){
  Complex matrix [] = {0.333333,-0.244017,0.910684,0.910684,0.333333,-0.244017,-0.244017,0.910684,0.333333};
  Complex *cubicCoeff;
  Complex *eigenVals;

  cubicCoeff = sec3d(matrix);
  eigenVals = cubicSolver(cubicCoeff);

  for(int i=0;i<3;i++){
    std::cout<<"Eigenvalue "<<i<<" = "<<eigenVals[i]<<std::endl;
  }

  return 0;
}
