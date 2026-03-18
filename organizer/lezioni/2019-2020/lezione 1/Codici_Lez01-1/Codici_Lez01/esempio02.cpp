/*
c++ -o esempio02 esempio02.cpp
*/

#include <iostream>

int main()
{
  int num;
  
  std::cout << "Inserisci un numero: " << std::endl;
  std::cin >> num;
  std::cout << "Il numero inserito e`: "
	    << num << std::endl;
  return 0;
}
