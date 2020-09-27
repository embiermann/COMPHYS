#include "integrate.h"

double integrate(double thetaMax){
  using namespace Genfun;

  SimpsonsRule rule;
  SimpleIntegrator integrator(0.,1.,rule,1.e3);

  Variable t;
  GENFUNCTION f=t; // Not sure what this is, placeholder

  return integrator(f);
}
