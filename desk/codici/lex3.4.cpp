#include <iostream>
#include <cstdlib>
#include "myLib.h"
#include <TCanvas.h>
#include <TH1F.h>

int main () {
	
	int seed, tries, N;
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
	std::cin >> N;
	std::cout << "Inserire numero di ripetizioni: ";
	std::cin >> tries;
	
	srand(seed);
	
	double rand, media, sum;
	
	TH1F pdf ("istogramma", "Istogramma-Exp", 100, xMin, xMax);
	
		for (int i = 0; i < tries; i++) {
			
			sum = 0;
			
			for (int r = 0; r < N; ++r) {
	
				rand = rand_FCI_Exp (xMin, xMax, mu);
				sum += rand;
			}
			
			media = sum / N;
			pdf.Fill(media);
		}
	
	TCanvas cnv;
	pdf.Draw();
	pdf.Fit("gaus");
	cnv.Print("istogramma.png", "png");
		
	return 0;
}
