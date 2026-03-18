#include <iostream>
#include <cstdlib>
#include <TCanvas.h>
#include <TH1F.h>
#include "myLib.h"

int main () {
	
	int seed, tries;
	double xMin, xMax, mu;
	
	std::cout << "Inserire seed: ";
	std::cin >> seed;
	std::cout << "Inserire mu: ";
	std::cin >> mu;
	std::cout << "Inserire x minima: ";
	std::cin >> xMin;
	std::cout << "Inserire x massima: ";
	std::cin >> xMax;
	std::cout << "Inserire # di numeri da generare: ";
	std::cin >> tries;
	
	srand(seed);
	
	isto_bin100_Exp (xMin, xMax, mu, tries);
	
	return 0;
}
