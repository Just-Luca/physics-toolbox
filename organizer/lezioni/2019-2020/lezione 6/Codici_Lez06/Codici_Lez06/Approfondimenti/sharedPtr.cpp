/*
c++ -o sharedPtr sharedPtr.cpp
*/

#include <optional>
#include <iostream>
#include <vector>
#include <memory>

#define N 10

void Print(std::shared_ptr<double> s1, std::shared_ptr<double> s2)
{
  std::cout << "\nFirst shared_ptr points to the memory cell : " << s1 << " which containts the value: " << *s1 << std::endl;
  std::cout <<  "Second shared_ptr points to the memory cell : " << s2 << " which containts the value: " << *s2 << std::endl;
}

template<typename T>
std::shared_ptr< std::vector<T> > create()
{
  return std::make_shared< std::vector<T> >();
}

void makeVectorAndDestroy()
{
  // ###############################################
  // # Alternative way to instantiate a shared_ptr #
  // ###############################################
  std::shared_ptr< std::vector<double> > sv1 = create<double>();
  sv1->push_back(3.8);
  sv1->push_back(4.2);
  std::cout << std::endl;
  for (unsigned int i = 0; i < sv1->size(); i++)
    std::cout << "Element [" << i << "] of the vector: " << (*sv1)[i] << std::endl;
}

int main()
{
  std::shared_ptr<double> s1(new double);
  std::shared_ptr<double> s2(new double);
  std::shared_ptr<double> s3 = s1;

  double* myDouble = new double;
  /* Compilation error: it's not possible to assign
     a standard pointer to a shared pointer
     std::shared_ptr<double> s4 = myDouble;
  */

  *s1 = 0.2;
  *s2 = 1.4;
  Print(s1,s2);

  s2 = s1;
  Print(s1,s2);

  *s1 = 2.6;
  Print(s1,s2);

  makeVectorAndDestroy();

  // ####################
  // # Test with arrays #
  // ####################
  std::cout << "\nShared pointers and arrays:" << std::endl;
  // We need to provide a custom delete because otherwise by defaut shared pointers
  // call delete var_name; but for arrays one needs to call delete[] var_name;
  // Arrays are fully supported by shared pointers since C++17
  // Creation: std::shared_ptr<double[]> myArray(new double[N]);
  // Access to elements: myArray[i];
  std::shared_ptr<double> myArray(new double[N], std::default_delete<double[]>());

  for (unsigned int i = 0; i < N; i++)
    myArray.get()[i] = static_cast<double>(i) / N; // get() retrieve the standard pointer

  for (unsigned int i = 0; i < N; i++)
    std::cout << "Element [" << i << "] = " << myArray.get()[i] << std::endl;

  return 0;
}
