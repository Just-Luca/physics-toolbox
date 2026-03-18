#include <cmath>	
#include <cstdlib>
#include "istogramma.h"
#include "myLib.h"
#include <iomanip> // stampa a terminale
#include <iostream>

istogramma::istogramma(int nBin, float min, float max) {

	nBin_p = nBin;
	min_p = min;
	max_p = max;
	step_p = (max_p - min_p)/nBin_p;
	binContent_p = new int [nBin_p];
	
	for (int i = 0; i < nBin_p; i++) {
		binContent_p[i] = 0;
	}
	
	underflow_p = 0; 
	overflow_p = 0;
	entries_p = 0;
	sum_p = 0;
	sumSq_p = 0; 
	// ho creato l'istogramma
}

istogramma::~istogramma() {

	delete [] binContent_p; // ho distrutto l'istogramma
}

int istogramma::Fill (float valore) {

	if (valore < min_p) {
	
		++underflow_p;
		return -1;
	} 
	
	if (valore >= max_p) {
	
		++overflow_p;
		return -1;
	}
	
	++entries_p; 
	
	if (entries_p == 0) {
	
		std::cout << "I valori sono tutti esterni all'istogramma."
			    << std::endl;
	}
	
	int bin; // indice del bin da incrementare
	bin = (valore - min_p)/step_p;
	++binContent_p[bin];
	sum_p += valore;
	sumSq_p += valore*valore;
	return bin;
}

float istogramma::GetMean () const {
	
	return sum_p/entries_p;
}

float istogramma::GetRMS () const {

	return sqrt(sumSq_p/entries_p - GetMean()*GetMean());
}

void istogramma::Print() const {
		
	if (entries_p != 0) {
	
		//cerca il bin con il numero massimo di conteggi
		int max = 0;
		for (int i = 0; i < nBin_p; ++i) {
		
			if (binContent_p[i] > max) {
		
				max = binContent_p[i];
			}
		}
	
		// fattore di rinormalizzazione per la rappresentazione dell'istogramma
		int scale = 50;
	
		// disegna l'asse delle y
		std::cout << "	+------------------------------------------------------------>"
			    << std::endl;
		    
		// disegna il contenuto dei bin
		for (int i = 0; i < nBin_p; ++i) {
	
			std::cout << std::fixed << std::setw(8) << std::setprecision(2)
				    << min_p + i*step_p << "|";
		
			int freq = int(scale*binContent_p[i]/max);
		
			for (int j = 0; j < freq; ++j) {
		
				std::cout << "#";
			}
		
			std::cout << std::endl;
		}

		std::cout << "	|\n" << std::endl;
	}
		
	else {
	
		std::cout << "I valori sono tutti esterni all'istogramma."
			    << std::endl;
	}   
}  
	
void istogramma::GetUnderflow () const {
	
	std::cout << "I conteggi sotto al valor minimo sono: "
		    << underflow_p << std::endl;
}

void istogramma::GetOverflow () const {
	
	std::cout << "I conteggi sopra al valor massimo sono: "
		    << overflow_p << std::endl;
}

float istogramma::GetIntegral () const {

	return (sum_p/entries_p) * (max_p - min_p);
}

