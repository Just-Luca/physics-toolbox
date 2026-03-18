#include <cmath>	
#include <cstdlib>
#include "istogramma.h"
#include "myLib.h"
#include <iomanip>
#include <iostream>

int main () {
	
	int seed, N, nBin;
	float min, max, xMax, xMin, rand;
	
	std::cout << "Inserisci seed: ";
	std::cin >> seed;
	
	srand(seed);
	
	std::cout << "Inserisci quanti numeri casuali vuoi generare: ";
	std::cin >> N;
	
	std::cout << "Inserisci l'intervallo in cui generare i numeri: ";
	std::cin >> xMin >> xMax;
	
	std::cout << "Inserisci gli estremi dell'istogramma [min,max): ";
	std::cin >> min >> max;
	
	std::cout << "Inserisci il numero di bin dell'istogramma: ";
	std::cin >> nBin;
	
	istogramma histo(nBin, min, max);
	
	int estrazioni = 10;
	
	for (int i = 0; i < N; i++) {
	
		rand = rand_media(xMin, xMax, estrazioni);
		histo.Fill(rand);
	}
	
	std::cout << "Media = "	<< histo.GetMean()
		    << std::endl;
		    
	std::cout << "Deviazione standard = " << histo.GetRMS()
		    << std::endl;
		    
	std::cout << "Integrale: " << histo.GetIntegral()
		    << std::endl;
	
	histo.GetUnderflow ();	    
	histo.GetOverflow ();
	
	histo.Print();
	
	return 0;
}
	
	
	
	
	
	
	
	
	
	
	
