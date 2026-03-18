/*
c++ -o esempio04 esempio04.cpp
*/

#include <iostream>

#define START 4

double raddoppia(double input)
{
  return input * 2;
}

int main()
{
  double valore_iniziale = START;
  double valore_finale = raddoppia(valore_iniziale);
  
  std::cout << valore_iniziale
	    << " x 2 = "
	    << valore_finale << std::endl;
  
  return 0;
}
