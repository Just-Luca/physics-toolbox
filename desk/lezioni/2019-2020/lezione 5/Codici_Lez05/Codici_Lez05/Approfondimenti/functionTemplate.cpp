/*
c++ -std=c++11 -o functionTemplate functionTemplate.cpp
*/

#include <iostream>
#include <string>

#include "lib.h"

int main ()
{
  double d1 = 1.2;
  double d2 = 3.14;

  std::cout << "Sum two double: " << d1 << " + " << d2 << " = ";
  std::cout << sum<double> (d1,d2) << std::endl;

  int i1 = 1;
  int i2 = 5;

  std::cout << "Sum two int: " << i1 << " + " << i2 << " = ";
  std::cout << sum (i1,i2) << std::endl;

  /*  This gives an error
      std::cout << "Mixed sum: " << sum (i1,d2) << std::endl; */

  // This can be done
  std::cout << "Mixed sum: " << i1 << " + " << d2 << " = ";
  std::cout << sum<double> (i1,d2) << std::endl;

  int    A = 2;
  double B = 2.22;
  std::cout << "A * 2 = " << double2(A) << std::endl;
  std::cout << "B * 2 = " << double2(B) << std::endl;

  // Default template arguments from c++11
  std::cout << "B * n = " << multiply<int,5>(B) << std::endl;
  std::cout << "B * n = " << multiply<>(B) << std::endl;

  std::string S = "O";
  std::cout << "S * n = " << multiply(S) << std::endl;

  return 0;
}
