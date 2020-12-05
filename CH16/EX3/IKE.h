//------------------------------------------------------------------------------------------------------------//
//                                                                                                            //
//                                                                                                            //
//                                                                                                            //
//------------------------------------------------------------------------------------------------------------//
#ifndef _IKE_h_
#define _IKE_h_
#include "QatGenericFunctions/Parameter.h"
#include "Eigen/Dense"
class IKE {
 public:
    
  // Constructor:
  IKE();
  
  // Destructor:
  virtual ~IKE();
  
  // Get the eccentricAnomaly
  double eccentricAnomaly (double x)const;
  
  // Accessors
  const Genfun::Parameter & e() const { return eccentricity;}
  Genfun::Parameter & e()  { return eccentricity;}
  
  const Genfun::Parameter & a() const { return semimajor;}
  Genfun::Parameter & a()  { return semimajor;}
  
  const Genfun::Parameter & t0() const { return t0Days;}
  Genfun::Parameter & t0()  { return t0Days;}
  
  const Genfun::Parameter & phi() const { return phiAngle;}
  Genfun::Parameter & phi()  { return phiAngle;}
  
  const Genfun::Parameter & theta() const { return thetaAngle;}
  Genfun::Parameter & theta()  { return thetaAngle;}
  
  const Genfun::Parameter & psi() const { return psiAngle;}
  Genfun::Parameter & psi()  { return psiAngle;}
  
  Eigen::Vector3d position(double timeInDays) const;
  
  
 private:
  
  const IKE & operator=(const IKE &right)=delete;
  
  Genfun::Parameter eccentricity;
  Genfun::Parameter semimajor;
  Genfun::Parameter t0Days;
  Genfun::Parameter phiAngle;
  Genfun::Parameter thetaAngle;
  Genfun::Parameter psiAngle;
  
  mutable Eigen::Matrix3d rotationMatrix;
  mutable double phiAngleCache;
  mutable double thetaAngleCache;
  mutable double psiAngleCache;
};
#endif
