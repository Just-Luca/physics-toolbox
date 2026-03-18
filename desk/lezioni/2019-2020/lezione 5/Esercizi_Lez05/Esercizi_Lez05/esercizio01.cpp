/*
c++ -o esercizio01 esercizio01.cpp
*/

#include <iostream>

#include "SimpleArray.h"

int main()
{
  SimpleArray<int> MyArray;
  unsigned int index;
  char answer;
  int num;

  do {
    std::cout << "Dire cosa si vuole fare (digitare la lettera corrispondente):" << std::endl;
    std::cout << "\tPush(i)     Pop(t)     Exit(e)" << std::endl;
    std::cin >> answer;
    if (answer == 'i')
      {
        std::cout << "Inserire un numero: ";
        std::cin >> num;
        MyArray.push(num);
      }
    else if (answer == 't')
      {
        std::cout << "Inserire l'indice dell'elemento che si vuole estrarre dall'array" << std::endl;
        std::cout << "(il numero di elementi dell'array e` " << MyArray.size() << "): ";
        std::cin >> index;
        num = MyArray.pop(index);
        std::cout << "E` stato estratto il numero " << num << std::endl;
      }
  } while (answer != 'e');

  unsigned int Nelem = MyArray.size();
  std::cout << "Numero di elementi dell'array = " << Nelem << std::endl;
  for (unsigned int i = 0; i < Nelem; i++)
    std::cout << "\telemento " << i << " = " << MyArray[i] << std::endl;

  return 0;
}
