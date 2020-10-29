#include "phiMatrix.h"

Eigen::Matrix<double,5,5> phiMatrix(Genfun::GENFUNCTION A, unsigned int n,
			  unsigned int nderiv){

  Eigen::MatrixXd matrix(5,5);
  
  for(int j=0;j<5;j++){
    Genfun::GENFUNCTION phij=Phin(j);

    for(int i=0;i<5;i++){
      if(nderiv==0){
        Genfun::GENFUNCTION f=Phin(i)*A*phij;
        matrix(i,j)=integral(f,n);
      }
      else if(nderiv==1){
	Genfun::GENFUNCTION phijP=phij.prime();
	Genfun::GENFUNCTION f=Phin(i)*A*phijP;
        matrix(i,j)=integral(f,n);
      }
      else if(nderiv==2){
	Genfun::GENFUNCTION phijPP=(phij.prime()).prime();
	Genfun::GENFUNCTION f=Phin(i)*A*phijPP;
        matrix(i,j)=integral(f,n);
      }
      
    }
  }
  return matrix;
}

Eigen::Matrix<double,5,5> phiMatrix(unsigned int n){
  
  Eigen::MatrixXd matrix(5,5);
  Genfun::Variable X;

  for(int j=0;j<5;j++){
    Genfun::GENFUNCTION phij=Phin(j);
    Genfun::GENFUNCTION phijPP=(phij.prime()).prime();
    Genfun::GENFUNCTION Hphij = -0.5*phijPP+0.5*X*X*phij;
    for(int i=0;i<5;i++){
      Genfun::GENFUNCTION f=Phin(i)*Hphij;
      matrix(i,j)=integral(f,n);
    }
  }
  return matrix;
}
    
    
