#include "Lib.h"

double rand_range (double xMin, double xMax) {
	
	return xMin + (xMax - xMin) * rand() / (1. * RAND_MAX);
}

double myEulero (int N_toy) { 
	
	int xMin = 0;
	int xMax = 1;
	
	double rv;
	double sum_k = 0.;
	double mean_k = 0.;
	
	for (int i = 0; i < N_toy; i++) {
		
		int k = 0;
		double sum_rv = 0.;
	
		while (sum_rv <= 1.) {
			
			rv = rand_range (xMin, xMax);
			sum_rv += rv;
			k++;	
		}
		
		sum_k += k;
	}
	
	return mean_k = sum_k/N_toy;
}

