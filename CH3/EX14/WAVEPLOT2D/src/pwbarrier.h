#include <Eigen/Dense>
#include <iostream>
#include <complex>
#include <string>
#include <sstream>

typedef std::complex<double> Complex;

Eigen::VectorXcd coeff(double v, double k);
Complex pwFunc(double x, double v, double k);
