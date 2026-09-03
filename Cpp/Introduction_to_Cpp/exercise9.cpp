/*

Exercise: declare a pointer and then try to assign a numeric value directly to it. What happens? Why?

*/

#include <iostream>

int main() {

  int* pointer;

  pointer = 5;
  std::cout << "value stored in the pointer " << pointer << '\n';  

  return 0;
}
