#include<iostream>
#include<cmath>
#include<sstream>
#include<math.h>
#include<iomanip>

// Function to calculate gamma given beta
double gamma_b(double beta){
  return 1.0/sqrt(1.0-(beta*beta));
}

// Function to calculate gamma given epsilon
double gamma_e(double epsilon){
  return 1.0/sqrt((2.0 - epsilon)*epsilon);
}

// Function to Find max beta
double max_beta(){
  double beta=0.9;
  double epsilon=0.1;
  double fracErr=0.0;

  while(fracErr<0.001){
    beta = 0.9 + beta/10.0;
    epsilon = epsilon/10.0;
    fracErr = abs(gamma_b(beta) - gamma_e(epsilon))/gamma_e(epsilon);
    std::cout<<"beta = ";
    std::cout<<std::setprecision(15)<<beta;
    std::cout<<" \t fracErr =";
    std::cout<<std::setprecision(15)<<fracErr<<"\n";
    }

  return beta;
}

// Create Table of Values and print max beta
int main(int argc, char **argv){

  double beta;
  double epsilon;
  double gamb;
  double game;

  //std::cout<<"Max beta = "<<max_beta()<<std::endl;
  max_beta();

  std::cout<<"\n";
  std::cout<<"\\begin{tabular}{|c|c||c|c|} \\hline \n";
  std::cout<<" $\\beta$ \t & \t  $\\gamma$ \t & \t ";
  std::cout<<"$\\epsilon$ \t & \t  $\\gamma$ \t \\\\ \n";
  std::cout<<"\\hline \\hline \n";
  for(int i=1;i<argc;i++){
    std::istringstream(argv[i])>>beta;
    gamb = gamma_b(beta);

    epsilon = 1. - beta;
    game = gamma_e(epsilon);

    std::cout<<beta<<"\t & \t"<<gamb<<"\t & \t";
    std::cout<<epsilon<<"\t & \t"<<game<<"\t \\\\ \n";
  }

  std::cout<<"\\hline \n";
  std::cout<<"\\end{tabular} \n"<<std::endl;

  return 0;
}
    



  
