//
// Find pi using the areas of isoceles triangles
//

#include <complex>
#include <iostream>
#include <cmath>
#include <iomanip>
#include <limits>

typedef std::complex<double> Complex;

int main() {
  // Follow threePi.cpp to find side lengths
  Complex x0=1.0;
  Complex x1(1.0/2.,sqrt(3.0)/2.0);
  unsigned int nsides=6;
  while (nsides < std::numeric_limits<int>::max()) {
    
    double lside = abs(x1-x0);
    double approx1=nsides*lside/2.0;
    double approx2=nsides*imag(x1)/2.0;

    // Approx pi by using circumference
    std::cout << "Sides " << nsides << "; approx1=" << std::setprecision(16) << approx1 << std::endl;
    

    // Approx pi by summing triangle areas (nb^2/4)
    std::cout << "Sides " << nsides << "; approx2=" << std::setprecision(16) << approx2 << std::endl;

    std::cout<<"\n \n";
    
    x1=(x1+x0)/abs(x1+x0);
    nsides *=2;
  }

  return 0;
}
		
