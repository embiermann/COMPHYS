#include "integrate.h"

Eigen::Vector3d  Integral(Genfun::GENFUNCTION f,
			  double lim1, double lim2, double N){
  Genfun::MidpointRule rule1;
  Genfun::TrapezoidRule rule2;
  Genfun::SimpsonsRule rule3;

  Genfun::SimpleIntegrator integrator1(lim1,lim2,rule1,N);
  Genfun::SimpleIntegrator integrator2(lim1,lim2,rule2,N);
  Genfun::SimpleIntegrator integrator3(lim1,lim2,rule3,N);

  double integral1 = integrator1(f);
  double integral2 = integrator2(f);
  double integral3 = integrator3(f);

  Eigen::Vector3d solns;
  solns << integral1, integral2, integral3;

  return solns;
}
