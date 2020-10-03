#include "QatGenericFunctions/GaussQuadratureRule.h"
#include "QatGenericFunctions/GaussIntegrator.h"
#include "QatGenericFunctions/Variable.h"
#include "QatGenericFunctions/Exp.h"

int main(){
  using namespace Genfun;
  
  const double rho = 2.7; // g cm^-3
  double n=(0.04*rho)*0.012*0.11; // cm^-2
  const double tau=1.2E6; // years
  const double lamb = 7.5; // cm

  Variable X;
  Exp exp;
  GENFUNCTION f= (n/tau)*(1-exp(-X/lamb));
  GaussLegendreRule rule(4);
  GaussIntegrator integrator(rule);

  std::cout << integrator(f) << std::endl;

  return 0;
}

  
      
