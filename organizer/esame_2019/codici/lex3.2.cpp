#include <iostream>
#include <cstdlib>
#include "myLib.h"
#include <TCanvas.h>
#include <TH1F.h>

int main () {
	
	int seed, tries;
	double xMin, xMax, yMin, yMax, media, varianza;
	
	std::cout << "Inserire seed: ";
	std::cin >> seed;
	std::cout << "Inserire x minima: ";
	std::cin >> xMin;
	std::cout << "Inserire x massima: ";
	std::cin >> xMax;
	std::cout << "Inserire y minima: ";
	std::cin >> yMin;
	std::cout << "Inserire y massima: ";
	std::cin >> yMax;
	std::cout << "Inserire # di numeri da generare: ";
	std::cin >> tries;
	
	srand(seed);
	
	isto_bin100_C (xMin, xMax, yMin, yMax, tries);
	
	return 0;
}
