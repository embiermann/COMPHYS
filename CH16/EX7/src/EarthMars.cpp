#include "EarthMars.h"
void EarthMars::addPoint (double timeDays, double RA, double D) {
  CelestialCoords p;
  p.RA=RA;
  p.D =D;
  _time.push_back(timeDays);
  _coords.push_back(p);
}
  
// Constructor
EarthMars::EarthMars():
  e1("Earth E", 0, 0.0, 0.2),
  a1("Earth A", 1, 0.9, 1.0),
  t1("Earth T", 0, -500.0, 500.0),
  phi1("Earth Phi", 0.000, -4.0*M_PI, 4.0*M_PI),
  theta1("Earth Theta", 23.4/180*M_PI, 0 , 0.6),
  psi1("Earth Psi", 0.860, -M_PI, M_PI),
  e2("Mars E", 0.073, 0.0, .2),
  a2("Mars A", 1.28, 0.9, 2.0),
  t2("Mars T", -22, -500.0, 500.0),
  phi2("Mars Phi", -0.03, -2.0*M_PI, 2.0*M_PI),
  theta2("Mars Theta", 0.42, 0 , 0.6),
  psi2("Mars Psi", -0.1, -M_PI, M_PI)
{
  earth.e().connectFrom(&e1);
  earth.a().connectFrom(&a1);
  earth.t0().connectFrom(&t1);
  earth.phi().connectFrom(&phi1);
  earth.theta().connectFrom(&theta1);
  earth.psi().connectFrom(&psi1);
  mars.e().connectFrom(&e2);
  mars.a().connectFrom(&a2);
  mars.t0().connectFrom(&t2);
  mars.phi().connectFrom(&phi2);
  mars.theta().connectFrom(&theta2);
  mars.psi().connectFrom(&psi2);
  
}

// Destructor:
EarthMars::~EarthMars(){
}

// Function Call Operator
double EarthMars::operator () () const {
  double chiSq=0.0;
  for (unsigned int i=0;i<_time.size();i++) {
    const CelestialCoords c=coords(_time[i]);
    chiSq+=pow(_coords[i].D-c.D,2)*1E5;
    double dRA=_coords[i].RA-c.RA;
    while (dRA<-M_PI) dRA+=2.0*M_PI;
    while (dRA>M_PI)  dRA-=2.0*M_PI;
    chiSq+=pow(dRA,2)*1E5;
  }
  
  return chiSq;
}

// Get the Celestial coords of mars vs. the time. 
EarthMars::CelestialCoords EarthMars::coords(double timeDays) const {
  Eigen::Vector3d p0=earth.position(timeDays);
  Eigen::Vector3d p1=mars.position(timeDays);
  Eigen::Vector3d p=p1-p0;
  double theta = asin(p[2]/p.norm());
  double phi   = atan2(p[1],p[0]);
  CelestialCoords c={phi,theta};
  return c;
}
