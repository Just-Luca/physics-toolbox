#include <iostream>
#include <cstdlib>
#include "myLib.h"
#include <TCanvas.h>
#include <TH1F.h>

int main () {
	
	int seed, tries;
	double xMin, xMax, media, varianza;
	
	std::cout << "Inserire seed: ";
	std::cin >> seed;
	std::cout << "Inserire minimo: ";
	std::cin >> xMin;
	std::cout << "Inserire massimo: ";
	std::cin >> xMax;
	std::cout << "Inserire # di numeri da generare: ";
	std::cin >> tries;
	
	srand(seed);
	media = rand_media (xMin, xMax, tries);
	varianza = rand_varianza (xMin, xMax, tries);
	
	std::cout << "La media di numeri casuali é: "
		    << media << std::endl;
	std::cout << "La varianza di numeri casuali é: "
		    << varianza << std::endl;
		    
	isto_bin100_G (xMin, xMax, tries);	    
	
	return 0;
}
