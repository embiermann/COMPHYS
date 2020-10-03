#include "integral.h"
#include "Phin.h"
#include "QatGenericFunctions/Variable.h"
#include <Eigen/Dense>


Eigen::Matrix<double,5,5> phiMatrix(Genfun::GENFUNCTION A, unsigned int n,
				    unsigned int nderiv=0);

Eigen::Matrix<double,5,5> phiMatrix(unsigned int n);
