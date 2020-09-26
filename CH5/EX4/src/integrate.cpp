#include "integrate.h"

double integrate(double v0){
  using namespace Genfun;
  
  SimpsonsRule rule;
  SimpleIntegrator integrator(0.,1.,rule,1.e3);

  Exp exp;
  Sqrt sqrt;
  Variable X;
  GENFUNCTION f=sqrt(1-v0*X*exp(-X*X/2));

  return integrator(f);
}
