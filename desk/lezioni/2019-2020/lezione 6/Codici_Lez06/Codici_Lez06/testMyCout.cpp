/*
c++ -o testMyCout testMyCout.cpp
*/

#include <iostream>

class mycout
{
public:
  // ########################
  // # Overload operator << #
  // ########################
  template<class T>
  mycout& operator<< (const T& buffer) // The returned value must be of type "mycout" to chain several << in one line
  {
    printf("Argument of size: %lu\n",sizeof(buffer));
    return *this; // "this" is a pointer to the instance of the class
  }
};

// ###############################
// # Immerge cout in a namespace #
// ###############################
namespace mystd
{
  mycout cout;
}

int main()
{
  mystd::cout << "Hello " << 10 << 3.14;
  return 0;
}
