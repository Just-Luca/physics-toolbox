//Questo programma genera N=10^4 numeri casuali secondo la distribuzione di Cauchy nell'intervallo (-5,5), utilizzando il metodo del Try&Catch: f=1/(PI(1+x^2))
//Definisce e riempie un istogramma TH1F con 100 bin per rappresentare la distribuzione di probabilità dei dati generati.

#include <iostream>
#include <cstdlib>
#include <TCanvas.h>
#include <TH1F.h>

#include "myLib.h"

int main()
{
	srand(time(NULL));
	int max_num = 10000;
	double numero_casuale = 0;

	TH1F myHisto("distribuzione_Cauchy", "istogramma", 100, -5, 5);

	for(int i=0; i<max_num; i++)
	{
		numero_casuale = rand_TAC(-5., 5., 0., 5.);

		myHisto.Fill(numero_casuale);
	}

	TCanvas cnv;
	myHisto.Draw();
	myHisto.Fit("gaus");
	cnv.Print("istogramma.png", "png");

	return 0;
}

