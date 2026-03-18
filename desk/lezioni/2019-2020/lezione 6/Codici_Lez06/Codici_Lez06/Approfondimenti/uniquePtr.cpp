/*
c++ -o uniquePtr uniquePtr.cpp
*/

#include <iostream>
#include <vector>
#include <memory>

#define N 10

void Print(std::unique_ptr<double>& u1, std::unique_ptr<double>& u2)
{
  std::cout << "\nFirst unique_ptr points to the memory cell : " << u1 << " which containts the value: " << *u1 << std::endl;
  std::cout <<  "Second unique_ptr points to the memory cell : " << u2 << " which containts the value: " << *u2 << std::endl;
}

template<typename T>
std::unique_ptr< std::vector<T> > create()
{
  std::unique_ptr< std::vector<T> > uv(new std::vector<T>());
  return std::move(uv);
  // Since C++14 one can also call std::make_unique
  // return std::make_unique< std::vector<T> >();
}

void makeVectorAndDestroy()
{
  // ###############################################
  // # Alternative way to instantiate a unique_ptr #
  // ###############################################
  std::unique_ptr< std::vector<double> > uv1 = create<double>();
  uv1->push_back(3.8);
  uv1->push_back(4.2);
  std::cout << std::endl;
  for (unsigned int i = 0; i < uv1->size(); i++)
    std::cout << "Element [" << i << "] of the vector: " << (*uv1)[i] << std::endl;
}

int main()
{
  std::unique_ptr<double> u1(new double);
  /* Unique pointers can not be copied in any way
     These two lines give compilation error
     std::unique_ptr<double> u2(u1);  // Copy constructor
     std::unique_ptr<double> u3 = u1; // Copy assignment
  */
  std::unique_ptr<double> u4(new double);

  *u1 = 0.2;
  *u4 = 1.4;
  Print(u1,u4);

  // u4 = u1; // This is not permitted with unique_ptr
  u4 = std::move(u1); // At this point u1 is empty, so it can not be used, we need to reset it
  u1.reset(new double(2.6));
  Print(u1,u4);

  u1.reset(new double(3.8));
  u4.reset(new double(4.2));
  Print(u1,u4);

  makeVectorAndDestroy();

  // ####################
  // # Test with arrays #
  // ####################
  std::cout << "\nUnique pointers and arrays:" << std::endl;
  // No need to provide a custom delete because unique pointers already support dynamical allocation of arrays
  std::unique_ptr<double[]> myArray(new double[N]);

  for (unsigned int i = 0; i < N; i++)
    myArray[i] = static_cast<double>(i) / N; // get() retrieve the standard pointer

  for (unsigned int i = 0; i < N; i++)
    std::cout << "Element [" << i << "] = " << myArray[i] << std::endl;

  return 0;
}
