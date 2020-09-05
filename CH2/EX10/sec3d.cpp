#include"diag3d.h"

//
// Return coeff of secular eqn given array
//

Complex * sec3d(Complex m[9]){
  Complex cubicEqn [4];

  cubicEqn[0] = -1.0;
  cubicEqn[1] = m[0]+m[4]+m[8];
  cubicEqn[2] = -m[0]*m[4] - m[0]*m[4] + m[1]*m[3] + m[2]*m[6] - m[4]*m[8] + m[5]*m[7];
  cubicEqn[3] = m[0]*m[4]*m[8] - m[0]*m[5]*m[7] - m[1]*m[3]*m[8] + m[1]*m[5]*m[6] + m[2]*m[3]*m[7] - m[2]*m[4]*m[6];

  return cubicEqn;
}
