#include <Eigen/Dense>
#include <iostream>
#include <complex>
#include <string>
#include <sstream>
typedef std::complex<double> Complex;

int main(int argc, char **argv){
  using namespace std;

  double v;
  double k;

  stringstream(argv[1])>>v;
  stringstream(argv[2])>>k;
  cout<<"k = "<<k<<endl;
  cout<<"v = "<<v<<"\n"<<endl;

  Complex I(0,1.0);
  Complex nk=k*sqrt(Complex(1-v));
  Complex mk=k*sqrt(Complex(1-2.*v));

  Eigen::VectorXcd Y(8);
  Y(0) = -exp(-2.*I*k)      ;
  Y(1) = 0.                 ;
  Y(2) = 0.                 ;
  Y(3) = 0.                 ;
  Y(4) = -I*k*exp(-2.*I*k)  ;
  Y(5) = 0.                 ;
  Y(6) = 0.                 ;
  Y(7) = 0.                 ;

  Eigen::MatrixXcd A(8,8);
  // First row
  A(0,0) = exp(2.*I*k)   ;
  A(0,1) = -exp(-2.*I*nk);
  A(0,2) = -exp(2.*I*k)  ;
  A(0,3) = 0.            ;
  A(0,4) = 0.            ;
  A(0,5) = 0.            ;
  A(0,6) = 0.            ;
  A(0,7) = 0.            ;
  
  // Second row
  A(1,0) = 0.         ;
  A(1,1) = exp(-I*nk) ;
  A(1,2) = exp(I*nk)  ;
  A(1,3) = -exp(-I*mk);
  A(1,4) = -exp(I*mk) ;
  A(1,5) = 0.         ;
  A(1,6) = 0.         ;
  A(1,7) = 0.         ;  
  
  // Third row
  A(2,0) = 0.         ;
  A(2,1) = 0.         ;
  A(2,2) = 0.         ;  
  A(2,3) = exp(I*mk)  ;
  A(2,4) = exp(-I*mk) ;
  A(2,5) = -exp(I*nk) ;
  A(2,6) = -exp(-I*nk);
  A(2,7) = 0.         ;

  // Fourth row
  A(3,0) = 0.           ;
  A(3,1) = 0.           ;
  A(3,2) = 0.           ;
  A(3,3) = 0.           ;
  A(3,4) = 0.           ;
  A(3,5) = exp(2.*I*nk) ;
  A(3,6) = exp(-2.*I*nk);
  A(3,7) = -exp(2.*I*k) ;

  // Fifth row
  A(4,0) = -I*k*exp(2.*I*k)   ;
  A(4,1) = -I*nk*exp(-2.*I*nk);
  A(4,2) = I*nk*exp(2.*I*nk)  ;
  A(4,3) = 0.                 ;
  A(4,4) = 0.                 ;
  A(4,5) = 0.                 ;
  A(4,6) = 0.                 ;
  A(4,7) = 0.                 ;

  // Sixth row
  A(0,0) = 0.              ;
  A(5,1) = I*nk*exp(-I*nk) ;
  A(5,2) = -I*nk*exp(I*nk) ;
  A(5,3) = -I*mk*exp(-I*mk);
  A(5,4) = I*mk*exp(I*mk)  ;
  A(0,5) = 0.              ;
  A(0,6) = 0.              ;
  A(0,7) = 0.              ;

  // Seventh row
  A(6,0) = 0.              ;
  A(6,1) = 0.              ;
  A(6,2) = 0.              ;
  A(6,3) = I*mk*exp(I*mk)  ;
  A(6,4) = -I*mk*exp(-I*mk);
  A(6,5) = -I*nk*exp(I*nk) ;
  A(6,6) = I*nk*exp(-I*nk) ;
  A(6,7) = 0.              ;

  // Eighth row
  A(7,0) = 0.                 ;
  A(7,1) = 0.                 ;
  A(7,2) = 0.                 ;
  A(7,3) = 0.                 ;
  A(7,4) = 0.                 ;
  A(7,5) = I*nk*exp(2.*I*nk)  ;
  A(7,6) = -I*nk*exp(-2.*I*nk);
  A(7,7) = -I*k*exp(2.*I*k)   ;

  // Solve
  Eigen::MatrixXcd AInv = A.inverse();
  Eigen::VectorXcd COEFF = AInv*Y;
  Complex R=COEFF(0), T=COEFF(7);

  // Print to cout
  cout << "Complex Coefficients" << endl;
  cout << COEFF << "\n \n";
  cout << "Reflection Coefficient: " << norm(R) << endl;
  cout << "Transmission Coefficient: " << norm(T) << endl;
}

