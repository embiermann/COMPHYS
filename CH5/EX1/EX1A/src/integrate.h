#include "QatGenericFunctions/Tanh.h"
#include "QatGenericFunctions/QuadratureRule.h"
#include "QatGenericFunctions/SimpleIntegrator.h"
#include <Eigen/Dense>

Eigen::Vector3d  Integral(Genfun::GENFUNCTION f,
			  double lim1, double lim2, double N);
