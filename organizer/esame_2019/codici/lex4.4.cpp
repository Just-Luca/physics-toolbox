#include <iostream>
#include <cstdlib>
#include "myLib.h"
#include <TCanvas.h>
#include <TH1F.h>
#include <cmath>

int main () {
	
	int seed, tries;
	double xMin, xMax, mu, sigma1, sigma2, media, varianza, rand1, rand2, mean, sum;
	
	std::cout << "Inserire seed: ";
	std::cin >> seed;
	std::cout << "Inserire mu: ";
	std::cin >> mu;
	std::cout << "Inserire sigma1: ";
	std::cin >> sigma1;
	std::cout << "Inserire sigma2: ";
	std::cin >> sigma2;
	std::cout << "Inserire # di numeri da generare: ";
	std::cin >> tries;
	
	srand(seed);
	
	xMin = -5; 
	xMax = 5; 
	
	TH1F pdf ("istogramma", "Istogramma-Gaus", 100, xMin, xMax);
	
	sum = 0;
	mean = 0;
	
	for (int i = 0; i < tries; i++) {
		
		rand1 = rand_TAC_Gaus(mu, sigma1);
		rand2 = rand_TAC_Gaus(mu, sigma2);
		
		sum = rand1 + rand2;
		
		mean = sum/2;
		
		pdf.Fill(mean);
	}	
	
	TCanvas cnv;
	pdf.Draw();
	pdf.Fit("gaus");
	cnv.Print("istogramma.png", "png");
	
	return 0;
}
