/*
c++ -o esempio03 esempio03.cpp

Array ed allocazione dinamica
*/

#include <iostream>

int main()
{
  int dim = 0;
  std::cout << "Inserisci la dimensione del vettore: ";
  std::cin >> dim;

  if (dim < 0)
  {
    std::cout << "Numero negativo" << std::endl;
    return -1;
  }

  // alloca dinamicamente un vettore di dim posti
  int* vec = new int[dim];
  
  // riempi il vettore
  for (int i = 0; i < dim; ++i)
  {
    vec[i] = i+1;
  }

  // stampa i posti pari del vettore
  std::cout << "Uso l'array\n";
  for (int i = 0; i < dim; ++i)
  {
    if (i%2 == 0)
    {
      std::cout << "al posto " << i << " c'è " << vec[i] << std::endl;
    }
  }

  // fai lo stesso con i puntatori
  std::cout << "Uso i puntatori\n";
  for (int* p = vec; (p-vec) < dim; ++p)
  {
    if ((p-vec)%2 == 0)
    {
      std::cout << "al posto " << p-vec << " c'è " << *p << std::endl;
    }
  }

  delete[] vec;

  return 0;
}
