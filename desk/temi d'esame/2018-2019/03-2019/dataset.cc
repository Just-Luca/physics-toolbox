#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>	
#include <cstdlib>
#include <vector>
#include <string>
#include "dataset.h"

//default
dataset::dataset() {

	int Ndati_p = 0;
	dati_p.push_back(0);
	double media_p = 0.;
	double devstd_p = 0.;
	double min_p = 0.;
	double max_p = 0.;
}

//costruttore
dataset::dataset(const char* nomefile) {
	
	std::ifstream Infile (nomefile);

	double t;
	int N = 0;

	while (true) {
	
		Infile >> t;
		if (Infile.eof() == true) break;
		
		dati_p.push_back(t);
		
		if (N == 0) {
			min_p = t;
			max_p = t;
		}
		
		else {
			if (t < min_p) min_p = t;
			if (t > max_p) max_p = t;
		}
				
		N++; 
	}
	
	Ndati_p = N;

	double sum = 0., sumSq = 0.;
  
	for (int i = 0; i < dati_p.size(); i++) {
	
		sum += dati_p[i];
		sumSq += dati_p[i]*dati_p[i];
	}
	
	media_p = sum/(float)Ndati_p;
	devstd_p = sqrt(sumSq/(float)Ndati_p - media_p*media_p);	
}

//distruttore
dataset::~dataset() {

	dati_p.clear();
}

//metodi

double dataset::GetMedia() {

	return media_p;
}

double dataset::GetDevstd() {

	return devstd_p;
}

int dataset::GetNdati() {
	
	return Ndati_p;
}

int dataset::GetDato(const int& i) {
	
	return dati_p[i-1];
}

double dataset::GetMin() {

	return min_p;
}

double dataset::GetMax() {

	return max_p;
}
























	
	
	
	
	
	
	
	
	
	
	
	
	



