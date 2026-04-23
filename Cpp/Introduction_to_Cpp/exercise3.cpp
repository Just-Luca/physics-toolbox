/*

c++ -o exercise3 exercise3.cpp
 
Exercise: write a code which asks user to insert one NATURAL number between 1 and 2, and then it prints to terminal either the chosen value, or an error message if some other natural number is inserted

*/

#include <iostream>

int main () {
    
  int x;

  std::cout << "Choose, 1 or 2: " << std::endl;
  std::cin >> x;

  if (x == 1) {
        std::cout << "x is ONE" << std::endl;
    }

  else if (x == 2) {
      std::cout << "x vale DUE" << std::endl;
    }

  else {
      std::cout << "x non vale ne' UNO, ne' DUE" << std::endl;
    }
  
  return 0;
}
