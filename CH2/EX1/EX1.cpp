#include<iostream>
#include<cmath>

int main(){

  std::cout<<"Machine Precision"<<std::endl;
  std::cout<<"\t \t Calculation \t Code \n";

  std::cout<<"Float: ";
  std::cout<<pow(2.,-23)<<" \t";
  std::cout<<std::numeric_limits<float>::epsilon();
  std::cout<<std::endl;

  std::cout<<"Double: ";
  std::cout<<pow(2.,-52)<<" \t";
  std::cout<<std::numeric_limits<double>::epsilon();
  std::cout<<std::endl;

  return 0;
}
