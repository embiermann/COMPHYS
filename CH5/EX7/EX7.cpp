#include <Eigen/Dense>
#include "QatGenericFunctions/Variable.h"
#include "QatGenericFunctions/FixedConstant.h"
#include "phiMatrix.h"
#include <iomanip>
int main(){
  using namespace Genfun;

  const double n=10;
  std::cout << std::fixed;  
  // PART A
  std::cout<<"Part A, X \n"<<std::endl;
  Variable X;
  GENFUNCTION opA=X;
  Eigen::MatrixXd A(5,5);
  A=phiMatrix(opA,n,0);
  std::cout<<A<<"\n"<<std::endl;

  // PART B
  std::cout<<"Part B, X^2 \n"<<std::endl;
  GENFUNCTION opB=X*X;
  Eigen::MatrixXd B(5,5);
  B=phiMatrix(opB,n);
  std::cout<<B<<"\n"<<std::endl;

  std::cout<<"Matrix A Squared: \n"<<std::endl;
  std::cout<<A*A<<"\n"<<std::endl;

  // Part C
  std::cout<<"Part C (1) d/dx \n"<<std::endl;
  FixedConstant opC=1.0;
  Eigen::MatrixXd C1(5,5);
  C1=phiMatrix(opC,n,1);
  std::cout<<C1<<"\n"<<std::endl;

  std::cout<<"Part C (2) d^2/dx^2 \n"<<std::endl;
  Eigen::MatrixXd C2(5,5);
  C2=phiMatrix(opC,n,2);
  std::cout<<C2<<"\n"<<std::endl;

  std::cout<<"Matrix C1 Squared: \n"<<std::endl;
  std::cout<<C1*C1<<"\n"<<std::endl;

  // Part D
  std::cout<<"Part D, H_SHO \n"<<std::endl;
  Eigen::MatrixXd D(5,5);
  D=phiMatrix(n);
  std::cout<<D<<"\n"<<std::endl;
  

  return 0;
}
  
