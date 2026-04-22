/*

c++ -o exercise2 exercise2.cpp

Exercise: write a code which prints square root of 2, cube of two and sine of pi/4

*/

#include <iostream>
#include <cmath>

int main () {

  double two = 2;
  double square_root_two = sqrt(two);
  std::cout << "Square root of two is: " << square_root_two << std::endl;
  
  double two_cube = pow(2., 3);
  std::cout << "Two cube is: " << two_cube << std::endl;
  
  double sin_45 = sin(M_PI/4.);
  std::cout << "sine of pi/4 is:  " << sin_45  << std::endl;
  
  return 0;
}
