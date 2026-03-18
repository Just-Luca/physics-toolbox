/*
c++ -o testSmartPtr testSmartPtr.cpp
*/

#include <iostream>
#include <memory>
#include <vector>

int main()
{
  std::shared_ptr<double> s1;
  std::shared_ptr<double> s2;
  s2 = s1;
  std::cout << "s1 contains: " << *s1 << "; s2 contains: " << *s2 << std::endl;
  /* Error: Segmentation fault because s1 and s2 have not yet been assigned
     Add before the assignment:
     s1 = std::make_shared<double>();
  */

  std::shared_ptr<std::vector<double>> s3(new std::vector<double>());
  s3->push_back(1.2);
  std::cout << "s3[0] contains: " << s3->operator[](0) << std::endl;
  /* Error: Compilation error. Correction:
     std::shared_ptr< std::vector<double> > s3(new std::vector<double>());
  */

  std::shared_ptr<double[]> sa1(new double[10]);
  /* Error: Compilation error due to double[], moreover we need to provide the proper destructor
     Correction:
     std::shared_ptr<double> sa1(new double[10], std::default_delete<double[]>());
  */

  std::shared_ptr<double> sa2;
  sa2 = std::make_shared<new double[10]>();
  /* Error: Compilation error due to the fact we can not use make_shared with arrays,
     moreover we need to provide the proper destructor. Correction:
     std::shared_ptr<double> sa2(new double[10], std::default_delete<double[]>());
  */


  std::unique_ptr<double> u1;
  std::unique_ptr<double> u2;
  u2 = u1;
  std::cout << "u1 contains: " << *u1 << "; u2 contains: " << *u2 << std::endl;
  /* Error: Segmentation fault
     There are mutiple errors:
     (a) u1 is not initialized: u1.reset(new double(1.2));
     (b) it's not possible for two unique pointers to point to the same memory: u2 = std::move(u1);
     (c) It's not possible to show the content of u1 because it has been reset with the instruction: u2 = std::move(u1);
  */

  double* d = new double(1.2);
  std::unique_ptr<double> u1;
  u1 = d;
  /* It's not possible to assign a standard pointer to a smart pointer
     Correction:
     u1.reset(new double(1.2));
   */

  std::unique_ptr<double> ua1(new double[10]);
  ua1[0] = 1.2;
  /* Error: Compilation error. Correction:
     std::unique_ptr<double[]> ua1(new double[10]);
  */

  return 0;
}
