/*
c++ -o esercizioLinkedList esercizioLinkedList.cpp
*/

#include <iostream>
#include <vector>

#include "SimpleLinkedList.h"

int main()
{
  SimpleLinkedList<int> MyLinkedList;
  char answer;
  int num;
  unsigned int index;

  do {
    std::cout << "Dire cosa si vuole fare (digitare la lettera corrispondente):" << std::endl;
    std::cout << "\tPush(i)     Pop(t)     Exit(e)" << std::endl;
    std::cin >> answer;
    if (answer == 'i')
      {
        std::cout << "Inserire un numero: ";
        std::cin >> num;
        MyLinkedList.push(num);
      }
    else if (answer == 't')
      {
        std::cout << "Inserire l'indice dell'elemento che si vuole estrarre dalla lista" << std::endl;
        std::cout << "(il numero di elementi della lista e` " << MyLinkedList.size() << "): ";
        std::cin >> index;
        num = MyLinkedList.pop(index);
        std::cout << "E` stato estratto il numero " << num << std::endl;
      }
  } while (answer != 'e');

  unsigned int Nelem = MyLinkedList.size();
  std::cout << "\nNumero di elementi della lista = " << Nelem << std::endl;
  for (unsigned int i = 0; i < Nelem; i++)
    std::cout << "\telemento " << i << " = " << MyLinkedList[i] << std::endl;

  // Test copy constructor
  SimpleLinkedList<int> MyLinkedList2 (MyLinkedList);
  std::cout << "\nNumero di elementi della lista (copy ctor) = " << Nelem << std::endl;
  for (unsigned int i = 0; i < Nelem; i++)
    std::cout << "\telemento " << i << " = " << MyLinkedList2[i] << std::endl;


  // #################
  // # Test iterator #
  // #################
  std::cout << "\nTest iterator on std::vectors" << std::endl;
  std::vector<int> MyVector;
  for (unsigned int i = 0; i < Nelem; i++) MyVector.push_back(i + 0.5);
  for (std::vector<int>::iterator it = MyVector.begin(); it != MyVector.end(); it++)
    std::cout << "\telemento " << *it << std::endl;

  std::cout << "\nTest iterator on SimpleLinkedList" << std::endl;
  for (SimpleLinkedList<int>::iterator it = MyLinkedList.begin(); it != MyLinkedList.end(); it++)
    std::cout << "\telemento " << *it << std::endl;


  return 0;
}
