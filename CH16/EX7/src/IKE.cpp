#include "IKE.h"
#include "QatGenericFunctions/FixedConstant.h"
// Constructor:
IKE::IKE():
	   eccentricity("Eccentricity", 0.0, 0.0, 2.0),
	   semimajor ("Semimajor axis", 1.0, 0.1, 10.0),
	   t0Days    ("T0 Days", 0.0, -500.0, 500.0),
	   phiAngle  ("Phi", 0.0, -M_PI, M_PI),
	   thetaAngle("Theta", 0.0, 0.0, M_PI),
	   psiAngle  ("Psi", 0.0, -M_PI, M_PI),
	   phiAngleCache(HUGE_VAL),
	   thetaAngleCache(HUGE_VAL),
	   psiAngleCache(HUGE_VAL)
{
}

// Destructor:
IKE::~IKE (){
}

// Function Call
double IKE::eccentricAnomaly ( double y) const {
  static const double tol=1.0E-13;
  double x=y;
  double ev=eccentricity.getValue();
  double f=y-x+ev*sin(x),fb=fabs(f);
  while (fb > tol ) {
    x-=f/(-1+ev*cos(x));
    f=y-x+ev*sin(x);
    fb=fabs(f);
    if (fb < tol) break;
  }
  return x;
}

Eigen::Vector3d IKE::position(double timeInDays) const {
  if (phiAngle.getValue()!=phiAngleCache ||
      thetaAngle.getValue()!=thetaAngleCache ||
      psiAngle.getValue()!=psiAngleCache ) {
    phiAngleCache=phiAngle.getValue();
    thetaAngleCache=thetaAngle.getValue();
    psiAngleCache=psiAngle.getValue();
    double sinPhi=sin(phiAngleCache), cosPhi=cos(phiAngleCache);
    double sinTheta=sin(thetaAngleCache), cosTheta=cos(thetaAngleCache);
    double sinPsi=sin(psiAngleCache), cosPsi=cos(psiAngleCache);
    rotationMatrix <<
      cosPsi*cosPhi-cosTheta*sinPhi*sinPsi, -sinPsi*cosPhi-cosTheta*sinPhi*cosPsi, sinTheta*sinPhi,
      cosPsi*sinPhi+cosTheta*cosPhi*sinPsi, -sinPsi*sinPhi+cosTheta*cosPhi*cosPsi, -sinTheta*cosPhi,
      sinTheta*sinPsi, sinTheta*cosPsi, cosTheta;
  }
  
  double x = (timeInDays-t0Days.getValue())*2.0*M_PI/365.0/pow(semimajor.getValue(), 3.0/2.0);
  double w=eccentricAnomaly (x);
  double R=semimajor.getValue()*(1-eccentricity.getValue()*cos(w));
  double X=semimajor.getValue()*(cos(w)-eccentricity.getValue());
  double ct=X/R;
  double st=sqrt((1-ct)*(1+ct))* (sin(w) > 0 ? 1: -1);
  double Y=R*st;
  double Z=0;
  
  return rotationMatrix*Eigen::Vector3d(X,Y,Z);
}

