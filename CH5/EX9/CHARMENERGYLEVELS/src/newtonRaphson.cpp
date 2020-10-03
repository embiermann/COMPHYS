#include "newtonRaphson.h"

double newtonRaphson(Genfun::GENFUNCTION f, double x){
  double xold;
  xold = x;
  while(1){
    x -= f(x)/f.prime()(x);
    if (std::abs(x-xold) < 1.0E-12) return x;
    xold=x;
  }
}
