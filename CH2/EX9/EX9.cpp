#include"quad.h"

int main(){
  Complex a = 1.0;
  Complex b [] = {4, 4, 4, (0,4), (0,4), (0,4), (0,4), (2,2),(2,2),(2,2)};
  Complex c [] = {0, 2, 6, -6, -4, 0, -6, -0, 6};
  quad_soln x;

  std::cout<<"\n";
  std::cout<<"\\begin{tabular}{|c|c|c||c|c|} \\hline \n";
  std::cout<<" a \t & \t  b \t & \t c \t & \t";
  std::cout<<"$x_1$ \t & \t  $x_2$ \t \\\\ \n";
  std::cout<<"\\hline \\hline \n";
  for(int i=0;i<9;i++){
    x = quad(a,b[i],c[i]);
    std::cout<<a<<"\t & \t"<<b[i]<<" \t & \t"<<c[i]<<" \t & \t";
    std::cout<<x.x1<<" \t & \t"<<x.x2<<" \t \\\\ \n";
  }

  std::cout<<"\\hline \n";
  std::cout<<"\\end{tabular} \n"<<std::endl;
  
  return 0;
}
