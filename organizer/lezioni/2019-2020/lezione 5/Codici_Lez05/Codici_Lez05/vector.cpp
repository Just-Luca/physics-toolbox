/*
c++ -o vector vector.cpp
*/

#include <iostream>
#include <vector>
#define N 10

int main ()
{
  // Define an std::vector
  std::vector<double> MyVector;

  // Fill the std::vector
  for (int i = 0; i < N; i++)
    MyVector.push_back (i * 3.14);

  // Vector dimension
  std::cout << "Number of elements = ";
  std::cout << MyVector.size() << std::endl;

  // It's possible to access the elements through [] or with the method at()
  for (int i = 0; i < MyVector.size(); i++)
    {
      std::cout << "Element " << i << ": ";
      std::cout << MyVector[i] << " (or equivalently with at(i): ";
      std::cout << MyVector.at(i) << ")" << std::endl;
    }

  return 0;
}
