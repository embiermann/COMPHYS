#include "charmS.h"

double charmE(double n, double res, bool l0){
  using namespace Genfun;

  Variable R;
  const double c=2.999792458e11; // mm s^-1
  const double hbar=6.5821e-10; // MeV s
  const double alpha=0.38;
  const double a=2.43e-3; // MeV^-1
  double mC = 1370; // MeV/c^2
  double hbarC = 1.973E-15; // MeV*mm
  
  GENFUNCTION V=-alpha*4.*hbar*c/(3*R) + R/(hbar*c*a*a);
  double E=-2000;
  double ntest;

  while(1){
    GENFUNCTION T = E - V;
    double rmax=newtonRaphson(T,0.05);
    GENFUNCTION integrand=Sqrt()(mC*T)/(M_PI*hbarC);

    RombergIntegrator integrator(0.0,rmax, RombergIntegrator::OPEN);
    
    if(l0) ntest = integrator(integrand) - 0.75; // l=0
    if(!l0) ntest = integrator(integrand) - 0.5; // l>0

    if (fabs(ntest-n) < res) return E;

    E += res;
  }
}

    
      
