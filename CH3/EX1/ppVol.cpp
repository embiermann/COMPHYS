#include "ppVol.h"

int main(){
  Eigen::Vector3d a(3.0, 0.0, 0.0);
  Eigen::Vector3d b(0.5, 2.0, 0.0);
  Eigen::Vector3d c(0.3, 0.2, 1.5);
  Eigen::MatrixXd M;
  M.col(0) = a;
  M.col(1) = b;
  M.col(2) = c;

  Parallelpiped P(M);

  std::cout<<"Volume using triple scalar product: "<<P.vecVol()<<std::endl;
  std::cout<<"Volume using determinant: "<<P.matrixVol()<<std::endl;

  return 0;
}

  
