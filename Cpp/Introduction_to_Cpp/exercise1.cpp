/*

c++ -o exercise1 exercise1.cpp
 
Exercise: write a code so that, given two natural numbers from terminal, it prints the fraction of the two

*/

#include <iostream>
come si dice rapporto in inglese

int main () {

  int number1, number2;

  std::cout << "First number: " << std::endl;
  std::cin >> number1;

  std::cout << "Second number: " << std::endl;
  std::cin >> number2;

  float rapporto = (float)number1 / number2;

  std::cout << "Il rapporto tra i due numeri è: "
      << rapporto << std::endl;

  return 0;
}
