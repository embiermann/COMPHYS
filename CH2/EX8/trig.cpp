#include<iostream>
#include<cmath>
#include<complex>

int main(int argc, char **argv){
  double x;
  std::complex<double> I(0,1);

  std::cout<<"\n";
  std::cout<<"\\begin{tabular}{|c||c|c||c|c|} \\hline \n";
  std::cout<<" x \t & \t $\\sin(ix)$ \t & \t $i\\sinh(x)$ \t & \t ";
  std::cout<<"$\\cos(ix)$ \t & \t  $\\cosh(x)$ \t \\\\ \n";
  std::cout<<"\\hline \\hline \n";
  for(int i=1;i<argc;i++){
    std::istringstream(argv[i])>>x;
    std::cout<<x<<"\t & \t"<<std::sin(I*x)<<"\t & \t"<<I*std::sinh(x)<<"\t & \t"<<std::cos(I*x)<<"\t & \t"<<I*std::cosh(x)<<"\t \\\\ \n";
  }
  std::cout<<"\\hline \n";
  std::cout<<"\\end{tabular} \n"<<std::endl;

  return 0;
}
