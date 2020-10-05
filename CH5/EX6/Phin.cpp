#include "Phin.h"

Genfun::FunctionNoop Phin(unsigned int n){
  
  Genfun::Variable X;
  Genfun::Exp exp;
  Genfun::HermitePolynomial H(n);
  double norm = pow(M_PI,-0.25)/sqrt(pow(2.,n)*tgamma(n+1));
  Genfun::GENFUNCTION F=norm*exp(-0.5*X*X)*H;
  return Genfun::FunctionNoop(&F);
}
