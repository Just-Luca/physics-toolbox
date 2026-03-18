#include <iostream>
#include "SimpleArray.h"

int main()
{
	SimpleArray<int> myArray(2);
	std::cout << "N elementi myArray = " << myArray.size() << std::endl;
	
	//std::cout << "Inserisci un numero: ";
	//std::cin >> num;
	//myArray.push(num);
	
	//int dim = myArray.size();
	//std::cout << "N elementi myArray = " << dim << std::endl;
		
	return 0;
}
