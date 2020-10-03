#include "QatGenericFunctions/Variable.h"
#include "QatGenericFunctions/FixedConstant.h"
#include "QatGenericFunctions/RombergIntegrator.h"
#include "QatGenericFunctions/Sqrt.h"
#include "newtonRaphson.h"
#include <cmath>

// Returns energy given level, resolution
// If l0 is on then it calculates the S States
// Otherwise, the function returns the P-wave state energy

double charmE(double n, double res=5, bool l0 = 1);
