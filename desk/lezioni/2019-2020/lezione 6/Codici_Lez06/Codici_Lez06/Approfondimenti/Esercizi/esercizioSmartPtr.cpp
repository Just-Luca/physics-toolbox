/*
c++ -o esercizioSmartPtr esercizioSmartPtr.cpp
*/

#include <iostream>

#include "SimpleArrayUniquePtr.h"
//#include "SimpleArraySharedPtr.h"

int main()
{
  SimpleArray<int> MyArray;
  char answer;
  int num;
  int index;

  do {
    std::cout << "Dimmi cosa vuoi fare (digita la lettera corrispondente):" << std::endl;
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
        std::cout << "Inserisci l'indice dell'elemento che vuoi estrarre dall'array" << std::endl;
        std::cout << "(il numero di elementi dell'array e` " << MyArray.size() << "): ";
        std::cin >> index;
        num = MyArray.pop(index);
        std::cout << "E` stato estratto il numero " << num << std::endl;
      }
  } while (answer != 'e');

  int Nelem = MyArray.size();
  std::cout << "N elementi MyArray = " << Nelem << std::endl;
  for (int i = 0; i < Nelem; i++)
    std::cout << "\telemento " << i << " = " << MyArray[i] << std::endl;

  return 0;
}
