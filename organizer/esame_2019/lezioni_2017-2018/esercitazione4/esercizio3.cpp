//Questo programma genera N=10000 numeri casuali da un pdf Normale con mu=0 e sigma=0,5 e li inserisce in un istogramma. Genera altri N numeri da una pdf Normale con mu=0 e sigma=2 e li inserisce nello stesso istogramma.

#include <iostream>
#include <cstdlib>
#include <TCanvas.h>
#include <TH1F.h>
#include <cmath>

#include "myLib.h"

int main()
{
 	srand(time(NULL));
	int N = 10000;
	double n_casuale, mu = 0, sigma1 = 0.5, sigma2 = 2;
	
	TH1F myHisto("istogramma", "distribuzione_normale", 100, mu-5*sigma2, mu+5*sigma2);
	
	for (int i=0; i<N; i++)
	{
		n_casuale = rand_TAC_gaus(mu, sigma1);
		myHisto.Fill(n_casuale);
		n_casuale = rand_TAC_gaus(mu, sigma2);
		myHisto.Fill(n_casuale);
	}
	
	TCanvas c1;
	myHisto.Draw();
	myHisto.Fit("gaus");
	c1.Print("isto.png","png");
}

	
