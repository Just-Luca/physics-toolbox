#include <iostream>
#include <cstdlib>
#include "myLib.h"

int main () {
	
	int seed;
	double min, max, rand;
	
	std::cout << "Inserire seed: ";
	std::cin >> seed;
	std::cout << "Inserire minimo: ";
	std::cin >> min;
	std::cout << "Inserire massimo: ";
	std::cin >> max;
	
	srand(seed);
	rand = rand_range (min, max);
	
	std::cout << "Il numero casuale é: "
		    << rand << std::endl;
	
	return 0;
}
