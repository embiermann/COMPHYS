#include<iostream>
#include<sstream>
#include<complex>
#include<cmath>

typedef std::complex<double> Complex;

Complex wavefunc(Complex k, Complex beta, double x){
  Complex wave;
  Complex i=(0.0,1.0);

  if(x<0.0){
    wave = exp(i*k*x) + (1.0/(1.0-i*beta) -1.0)*exp(-i*k*x);
  }
  else{
    wave = (1.0/(1.0-i*beta))*exp(i*k*x);
  }

  return wave;
}

double reflec(double E, double V, double m){
  double hbar=4.1357e-15;
  return 1.0/(1.0+(2.0*hbar*hbar*E/(m*V*V)));
}

double transmit(double E, double V, double m){
  double hbar=4.1357e-15;
  return 1.0/(1.0+(m*V*V/(2.0*hbar*hbar*E)));
}

int main(int argc, char **argv){
  double V;
  double E;
  double m=0.511;
  double hbar=4.1357e-15;
  double x;
  Complex k;
  Complex beta;
  
  std::istringstream(argv[1])>>V;
  std::istringstream(argv[2])>>E;
  std::istringstream(argv[3])>>x;

  k = sqrt(2.0*m*E)/hbar;
  beta = m*V/(hbar*hbar*k);

  std::cout<<"Wavefunction at x = "<<x<<" is "<<wavefunc(k,beta,x)<<std::endl;
  std::cout<<"R = "<<reflec(E,V,m)<<std::endl;
  std::cout<<"T = "<<transmit(E,V,m)<<std::endl;

  return 0;
}
		     
  
  
