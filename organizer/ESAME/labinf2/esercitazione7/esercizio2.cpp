#include <iostream>
#include "SimpleArray.h"

int main()
{
	SimpleArray<char> MyArray;
	char answer;
	char lettera;
	int index;
	
	do
	{
    	std::cout << "Dimmi cosa vuoi fare (digita la lettera corrispondente):" << std::endl;
    	std::cout << "Push(i)  Pop(t)  Exit(e) " << std::endl;
    	std::cin >> answer;
   		if (answer == 'i')
    	{
			std::cout << "Inserisci una lettera: ";
			std::cin >> lettera;
			MyArray.push(lettera);
    	}
    	else if (answer == 't')
    	{
			std::cout << "Inserisci l'indice dell'elemento che vuoi estrarre dall'array ";
			std::cout << "(il numero di elementi dell'array è " << MyArray.size() << "): ";
			std::cin >> index;
			lettera = MyArray.pop(index);
			std::cout << "Hai estratto la lettera " << lettera << std::endl;
    	}
	} while (answer!='e');

	int Nelem = MyArray.size();
	std::cout << "N elementi MyArray = " << Nelem << std::endl;
	for (int i = 0; i < Nelem; ++i)
    	std::cout << " elemento " << i << " = " << MyArray[i] << std::endl;

 	return 0;
}
