/*

Esempio: suddivisione di un programma in file/librerie

*/

#include <iostream>
#include "myLib.h"

int main ()
{
  double valore_iniziale = 4;
  double valore_finale = raddoppia(valore_iniziale);

  std::cout << "Raddoppia: " << valore_iniziale << " x 2 = "
            << valore_finale << std::endl;

  return 0;
}
