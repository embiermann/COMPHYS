#include <iostream>
#include <Eigen/Dense>

struct Parallelpiped{

  Eigen::Matrix3d M;

  // Return Components
  Eigen::Vector3d getA() const {return M.col(0);}
  Eigen::Vector3d getB() const {return M.col(1);}
  Eigen::Vector3d getC() const {return M.col(2);}

  // Volume from vectors
  double vecVol() {
    Eigen::Vector3d a = M.col(0);
    Eigen::Vector3d b = M.col(1);
    Eigen::Vector3d c = M.col(2);
    return std::abs((b.cross(a).dot(c)));
  }

  // Volume from matrix
  double matrixVol() { return M.determinant();}

  
};
