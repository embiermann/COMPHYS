#ifndef  _EARTHMARS_H_
#define  _EARTHMARS_H_
#include "IKE.h"
#include "QatDataModeling/ObjectiveFunction.h"
#include <vector>
class EarthMars:public ObjectiveFunction {
public:

  // 
  struct CelestialCoords {
    double RA;
    double D;
  };
  
  // Constructor
  EarthMars();

  // Destructor:
  ~EarthMars();
  
  // Function Call Operator
  virtual double operator () () const;

  // Get the Celestial coords of mars vs. the time. 
  CelestialCoords coords(double timeDays) const;

  // Add a data point:
  void addPoint (double timeDays, double RA, double D);

  // Access to each planet
  
  const IKE & getEarth() const { return earth;}
  IKE & getEarth() { return earth;}

  const IKE & getMars() const { return mars;}
  IKE & getMars() { return mars;}

  Genfun::Parameter e1,a1,t1, phi1, theta1, psi1;
  Genfun::Parameter e2,a2,t2, phi2, theta2, psi2;

  IKE earth;  // Find earth position from inverse Kepler Equation
  IKE mars;   // Find mars  position from inverse Kepler Equation
  
private:


  std::vector<double>          _time;
  std::vector<CelestialCoords> _coords;
};
#endif
