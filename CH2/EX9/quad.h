#ifndef _MAIN_H_
#define _MAIN_H_

#include<iostream>
#include<sstream>
#include<complex>
#include<cmath>

typedef std::complex<double> Complex;

struct quad_soln{
  Complex x1;
  Complex x2;
} ;

quad_soln quad(Complex a, Complex b, Complex c);

#endif

