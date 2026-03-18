#include <iostream>
#include "SimpleArray.h"

int main()
{
	int elementi = 10;
	//array di int
	SimpleArray<int> arrayInt(elementi);
	std::cout << "L'array di interi è: " << std::endl;
	for(int i=0; i<elementi; ++i)
		arrayInt.element(i) = 2*i;
	for(int i=0; i<elementi; ++i)
		std::cout << "elemento " << i << " = " << arrayInt.element(i) << std::endl; //con metodo element
	
	//array di float
	SimpleArray<float> arrayFloat(elementi);
	std::cout << "L'array di numeri reali è: " << std::endl;
	for(int i=0; i<elementi; ++i)
		arrayFloat.element(i) = 0.5 + arrayInt.element(i);
	for(int i=0; i<elementi; ++i)
		std::cout << "elemento " << i << " = " << arrayFloat[i] << std::endl; //con operatore
		
	return 0;
}

