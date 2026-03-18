//generare la media di n numeri casuali N volte e inserire i dati in un istogramma

#include <iostream>
#include <cstdlib>
#include "myLib.h"
#include <TCanvas.h>
#include <TH1F.h>
#include <cmath>
#define N 1000

int main () {
	
	int seed, tries;
	double xMin, xMax, media, varianza, rand, mean, dev_std;
	
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
	
	std::cout << "La media dei primi (tries)numeri casuali é: "
		    << media << std::endl;
		    
	TH1F pdf ("istogramma", "Istogramma-Gaus", 100, xMin, xMax);


	for (int i = 0; i < N; i++) {
	
		mean = 0;
	
		for (int j = 0; j < tries; j++) {
	
		 	rand = rand_range (xMin, xMax);
		 	mean += rand;
		 }
		
		mean /= tries;
		pdf.Fill(mean);
	}
	
	std::cout << "La media delle medie dei numeri casuali é: "
		    << mean << std::endl;
		    
	/*double sum, casual;
		    
	for (int i = 0; i < N; i++) {
	
		sum = 0;
	
		for (int j = 0; j < tries; j++) {
	
		 	casual = rand_range (xMin, xMax);
		 	sum += casual;
		 }
		
		sum /= tries;
	}*/
	    
	dev_std = sqrt ((mean*mean)/tries - (mean/tries)*(mean/tries));
	
	std::cout << "La deviazione standard delle medie dei numeri casuali é: "
		    << dev_std << std::endl;
	
	TCanvas cnv;
	pdf.Draw();
	pdf.Fit("gaus");
	cnv.Print("istogramma.png", "png");
			
	return 0;
}
