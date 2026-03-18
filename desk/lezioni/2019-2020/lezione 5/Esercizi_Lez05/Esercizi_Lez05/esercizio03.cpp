/*
c++ -o esercizio03 esercizio03.cpp complesso.cc
*/

#include <iostream>
#include <string>
#include <vector>

#include "complesso.h"

int main()
{
  complesso Z0 (0,0);
  std::vector <complesso> complexVector;
  double re = 0., im = 0.;

  do {
    std::cout << "Insert real and imaginary parts of a complex number (0 0 to exit): ";
    std::cin >> re >> im;
    complesso z(re,im);
    complexVector.push_back(z);
  } while (re != 0 && im != 0);

  complesso sum (0,0);
  for (int i = 0; i < complexVector.size(); i++)
    {
      sum = sum + complexVector[i];
    }
  std::cout << "\nThe sum of all inserted complex numbers is: ";
  sum.Print();

  return 0;
}
