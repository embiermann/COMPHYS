#include"quad.h"

quad_soln quad(Complex a, Complex b, Complex c){
  quad_soln x;

  x.x1 = (-b + sqrt(b*b - 4.0*a*c))/(2.0*a);
  x.x2 = (-b - sqrt(b*b - 4.0*a*c))/(2.0*a);

  return x;
}
  
