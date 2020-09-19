#include "pwbarrier.h"

double pwFunc(double x){
  using namespace std;

  double v = v;
  double k = k;
  Eigen::VectorXcd COEFF=coeff(v, k);
  Complex I(0,1.0);
  Complex nk=k*sqrt(Complex(1-v));
  Complex mk=k*sqrt(Complex(1-2.*v));
  Complex A, B, C, D, F, G, H, J, L;
  Complex wavefunc;
  
  B = COEFF(0);
  C = COEFF(1);
  D = COEFF(2);
  F = COEFF(3);
  G = COEFF(4);
  H = COEFF(5);
  J = COEFF(6);
  L = COEFF(7);

  wavefunc  = exp(I*k*x) + B*exp(-I*k*x)
            + C*exp(I*nk*x) + D*exp(-I*nk*x)
            + F*exp(I*mk*x) + G*exp(-I*mk*x)
            + H*exp(I*nk*x) + J*exp(-I*nk*x)
            + L*exp(I*k*x);
  
  return real(conj(wavefunc)*wavefunc);

}
  
