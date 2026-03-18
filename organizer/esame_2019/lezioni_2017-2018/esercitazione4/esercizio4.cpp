//Questo programma genera M=10000 numeri casuali da un pdf Normale con mu=0 e sigma=0,5 e genera altri M numeri da una pdf Normale con mu=0 e sigma=2. Per ogni coppia di numeri estratti, ne calcola la media e inserisce il valore ottenuto in un istogramma.

#include <iostream>
#include <cstdlib>
#include <TCanvas.h>
#include <TH1F.h>
#include <cmath>

#include "myLib.h"

int main()
{
 	srand(time(NULL));
	int N = 5000;
	int M = 10000;	
	double mu = 0, sigma1 = 0.5, sigma2 = 2;
	
	TH1F myHisto ("istogramma", "distribuzione_normale", 100, -0.3, 0.3);
	
	for(int i=0; i<N; i++)
	{
		double media = 0, n_casuale;
		for(int j=0; j<M; j++)
		{
			n_casuale = rand_TAC_gaus(mu, sigma1);
			media += n_casuale;
			n_casuale = rand_TAC_gaus(mu, sigma2);
			media += n_casuale;
		}
		media /= 2*N;
		myHisto.Fill(media);
	}
	TCanvas c1;
	myHisto.Draw();
	myHisto.Fit("gaus");
	c1.Print("isto.png","png");

	return 0;
}
