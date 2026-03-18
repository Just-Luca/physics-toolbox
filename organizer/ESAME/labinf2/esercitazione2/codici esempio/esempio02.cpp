/*
c++ -o esempio02 esempio02.cpp

Funzioni e passaggio di parametri
*/

#include<iostream>

// Vari modi di scrivere le raddoppia
double raddoppia(double input)
{
  return input * 2;
} 

double raddoppia2(double input)
{
  input = input * 2;
  return input;
} 

double raddoppiaPointer(double *input)
{
  *input = *input * 2;
  return *input;
} 

double raddoppiaReference(double &input)
{
  input = input * 2;
  return input;
} 


// main del programma
int main (int numArg, char *listArg[])
{
  double valore_iniziale, valore_finale;

  std::cout << std::endl
            << "Funzione raddoppia che non modifica il valore iniziale ma restituisce solamente il valore raddoppiato:"
            << std::endl << std::endl;

  valore_iniziale = 4;
  valore_finale = raddoppia(valore_iniziale);
  std::cout << "1) raddoppia:          " 
            << valore_iniziale 
            << " x 2 = "
            << valore_finale << std::endl;
  
  valore_iniziale = 4;
  valore_finale = raddoppia2(valore_iniziale);
  std::cout << "2) raddoppia2:         " 
            << valore_iniziale 
            << " x 2 = "
            << valore_finale << std::endl;
  
  std::cout << std::endl
            << "Funzione raddoppia che agisce dirattamente sul valore passato e quindi restituisce il valore raddoppiato:"
            << std::endl << std::endl;

  valore_iniziale = 4;
  valore_finale = raddoppiaPointer(&valore_iniziale);
  std::cout << "3) raddoppiaPointer:   " 
            << valore_iniziale 
            << " x 2 = "
            << valore_finale << " (modifica la variabile \"valore_iniziale\" esterna alla funzione!) " << std::endl;
  
  valore_iniziale = 4;
  valore_finale = raddoppiaReference(valore_iniziale);
  std::cout << "4) raddoppiaReference: " 
            << valore_iniziale 
            << " x 2 = "
            << valore_finale <<  " (modifica la variabile \"valore_iniziale\" esterna alla funzione!) " << std::endl;
  
  return 0;
}
