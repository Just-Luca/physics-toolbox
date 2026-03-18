//Questo programma estrae M=10000 numeri casuali da una distribuzione gaussiana nel range [a, b] e calcola la media dei numeri estratti. Ripete la procedura per 1000 volte e inserisce i valori medi in un istogramma TH1F. Calcola la media e la deviazione standard dei valori calcolati nelle 1000 ripetizioni.

#include <iostream>
#include <cstdlib>
#include <TCanvas.h>
#include <TH1F.h>
#include <cmath>

#include "myLib.h"

int main()
{
 	srand(time(NULL));
	int N = 1000;
	int M = 10000;
	double mu, sigma;
	
	std::cout<< "Impostare MU e SIGMA della pdf gaussiana: ";
	std::cin >> mu >> sigma;	
	
	TH1F myHisto("istogramma", "distribuzione_gaussiana", 100, mu-5*sigma/sqrt((double)M), mu+5*sigma/sqrt((double)M));
	
	double media = 0., n_casuale, nuova_media = 0., SigmaMu = 0.;
	for (int i=0; i<N; i++)
	{
		for (int j=0; j<M; j++)
		{
			n_casuale = rand_TAC_gaus(mu, sigma);
			media += n_casuale;
		}
		media /= M;
		myHisto.Fill(media);
		nuova_media += media;
		SigmaMu += media*media;
	}
	
	nuova_media /= (double)N;
	SigmaMu = sqrt(SigmaMu/(double)N - nuova_media*nuova_media);
	
	std::cout << "Per il TLC, la deviazione std della media di 10000 numeri estratti da una pdf gaussiana con sigma = "
			<< sigma <<" è: " << sigma/sqrt((double)M) << std::endl;
	std::cout << "Il valore stimato per la dev std della media campionando la pdf della media è: " << SigmaMu <<std::endl;
	std::cout << "Il rapporto tra dev std della pdf gaussiana di partenza e dev std della media è: "<< sigma/SigmaMu << std::endl;
		
	
	TCanvas c1;
	myHisto.Draw();
	c1.Print("isto.png","png");

	return 0;
 }
 
 

