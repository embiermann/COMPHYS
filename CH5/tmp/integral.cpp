#include "integral.h"

double integral(Genfun::GENFUNCTION integrand, unsigned int n){

  Genfun::GaussHermiteRule rule(n);
  Genfun::GaussIntegrator integrator(rule);

  return integrator(integrand);
}
