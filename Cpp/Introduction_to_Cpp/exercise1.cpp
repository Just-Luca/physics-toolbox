/*

c++ -o exercise1 exercise1.cpp
 
Exercise: write a code so that, given two natural numbers from terminal, it prints the ratio of the two

*/

#include <iostream>

int main () {

  int number1, number2;

  std::cout << "First number: " << std::endl;
  std::cin >> number1;

  std::cout << "Second number: " << std::endl;
  std::cin >> number2;

  float ratio = (float)number1 / number2;

  std::cout << "The ratio is: "
      << ratio << std::endl;

  return 0;
}
