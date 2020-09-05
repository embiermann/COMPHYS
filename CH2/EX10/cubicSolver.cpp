#include"diag3d.h"

//
// Solve Cubic Equation
//

Complex * cubicSolver(Complex coeff[4]){
  Complex x[3];
  Complex ksi = -1.0+sqrt(-3)/2.0;
  Complex bigC;
  Complex del0;
  Complex del1;

  // delta_0 = b^2 - 3ac
  del0 = pow(coeff[1],2)-3.*coeff[0]*coeff[2];
  // delta_1 = 2b^2 - 9ac + 27a^2d
  del1 = 2.*pow(coeff[1],3)-9.*coeff[0]*coeff[1]*coeff[2]+27.*pow(coeff[0],2)*coeff[4];
  // C = (1/2*(delta_1+/-sqrt(delta_1^2-4delta_2^3)))^(1/3)
  bigC = pow(0.5*(del1+sqrt(del1*del1-4.*pow(del0,3))),1./3.);
  if(abs(bigC)<=0.0001){
    bigC = pow(0.5*(del1-sqrt(del1*del1-4.*pow(del0,3))),1./3.);
  }

  for(int k=0;k<3;k++){
    x[k] = -1./(3.*coeff[0])*(coeff[1]+pow(ksi,k)*bigC+del0/(pow(ksi,k)*bigC));
  }

  return x;
}
