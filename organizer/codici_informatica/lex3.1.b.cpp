#include <iostream>
#include "myLib.h"

int main () {

	double min, max, rand, count;
	
	std::cout << "Inserire # di numeri da generare: ";
	std::cin >> count;
	
	
	rand = rand_range (min, max);
	
	std::cout << "Il numero casuale é: "
		  << rand << std::endl;
	
	return 0;
}
