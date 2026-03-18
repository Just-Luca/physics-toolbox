// c++ -o main myLib.cc istogramma.cc main.cpp
#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include "istogramma.h"
#include "myLib.h"

int main () {

	// istrogramma di "default"
	istogramma DefaultHisto; 
	
	const int Nbin=30;
	const float min=0.;
	const float max=10.;
	// costruttore con valori di inizializzazione
	istogramma MyHisto (Nbin, min, max); 
	 
	// copy constructor
	istogramma HistoCopy (MyHisto);	
	istogramma HistoCopy2 = MyHisto;
	
	
	int N=10000;
	int estrazioni=10;
	float random;
	for (int i=0; i<N; i++) {
		random = rand_CLT (min, max, estrazioni);
		MyHisto.Fill(random);
	}
	
	std::cout<<"Media = "<< MyHisto.GetMean() <<std::endl;
	std::cout<<"Dev.Std = "<< MyHisto.GetRMS() <<std::endl;
	
	
	istogramma MyHisto2 (Nbin, min, max); 
	for (int i=0; i<N; i++) {
		random = rand_range (min, max);
		MyHisto2.Fill(random);
	}
	istogramma SumHisto;
	SumHisto = MyHisto+MyHisto2;
	
	SumHisto.Print();
	

			
	return 0;
}



