#include <Eigen/Dense>
#include "QatGenericFunctions/GaussQuadratureRule.h"
#include "QatGenericFunctions/GaussIntegrator.h"

#include "Phin.h"

int main(){
  
  using namespace Genfun;
  
  Eigen::MatrixXd A(5,5);

  for (int j=0; j<A.cols(); j++)
    for (int i=0; i<A.rows(); i++)
      {
	GENFUNCTION P1=Phin(i);
	GENFUNCTION P2=Phin(j);
	GENFUNCTION f=P1*P2;

	GaussHermiteRule rule(4);
	GaussIntegrator integrator(rule);

	A(i,j) = integrator(f);
      }

  std::cout << A << std::endl;
  
  return 0;
}
