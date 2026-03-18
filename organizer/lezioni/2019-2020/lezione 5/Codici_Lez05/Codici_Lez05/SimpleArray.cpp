/*
c++ -o SimpleArray SimpleArray.cpp
*/

#include <iostream>
#include "SimpleArray.h"
#define N 10

int main()
{
  // Simple array with int
  SimpleArray<int> arrayInt(N);
  std::cout << "Array filled with int" << std::endl;

  // Filling
  for(unsigned int i = 0; i < N; i++)
    arrayInt.element(i) = 2 * i;

  // Readback
  for(unsigned int i = 0; i < N; i++)
    std::cout << "   element " << i << " = " << arrayInt.element(i) << std::endl;

  // Simple array with float
  SimpleArray<float> arrayFloat(N);
  std::cout << "\nArray filled with float" << std::endl;

  // Filling
  for(unsigned int i = 0; i < N; i++)
    arrayFloat.element(i) = 0.5 + arrayInt.element(i);

  // Readback
  for(unsigned int i = 0; i < N; i++)
    std::cout << "   element " << i << " = " << arrayFloat[i] << std::endl;

  return 0;
}
