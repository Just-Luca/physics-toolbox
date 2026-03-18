#include <iostream>
#include <cstdlib>
#include "myLib.h"
#include <cmath>
#include <TCanvas.h>
#include <TH1F.h>

int main () {
	
	int seed, N;
	double xMin, xMax, yMin, yMax, mu, sigma;
	
	std::cout << "Inserire seed: ";
	std::cin >> seed;
	std::cout << "Inserire xMin: ";
	std::cin >> xMin;
	std::cout << "Inserire xMax: ";
	std::cin >> xMax;
	std::cout << "Inserire yMin: ";
	std::cin >> yMin;
	std::cout << "Inserire yMax: ";
	std::cin >> yMax;
	std::cout << "Inserire sigma: ";
	std::cin >> sigma;
	std::cout << "Inserire mu: ";
	std::cin >> mu;
	std::cout << "Inserire N: ";
	std::cin >> N;
	
	srand(seed);
	
	int nHit = 0;
	
	for (int i = 0; i < N; i++) {
	
		if (HitMiss_Gaus(xMin, xMax, yMin, yMax, mu, sigma) == true) {
		
			nHit++;
		}
	}
		
	double A = Area (xMin, xMax, yMin, yMax);
	double I = Integral_HM (nHit, N, A);
	double p = p_HM (nHit, N);
	double Var = Var_HM (A, p, N);
	double StdVar = StdVar_HM(Var);
	
	std::cout << "I = " << I << " ";
	std::cout << "+- ";
	std::cout << StdVar << std::endl;
	
	return 0;
}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
