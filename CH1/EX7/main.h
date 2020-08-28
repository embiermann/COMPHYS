#ifndef _MAIN_H_
#define _MAIN_H_

#include<iostream>
#include<sstream>

struct inputs{
  int in1;
  int in2;
};

inputs parse(int argc, char ** argv);
int add(inputs x);
void print(inputs x, int sum);

#endif
