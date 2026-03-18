//Questo programma genera N=10^4 numeri casuali distribuiti secondo una pdf esponenziale con mu=0.25 nell'intervallo [0,1], utilizzando il metodo della funzione cumulativa inversa: f=1/m(exp(-x/m).
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

	TH1F myHisto("distribuzione_FCI", "istogramma", 100, 0, 2);

	for(int i=0; i<max_num; i++)
	{
		numero_casuale = rand_FCI_exp(0.25);
		myHisto.Fill(numero_casuale);
	}

	TCanvas cnv;
	myHisto.Draw();
	myHisto.Fit("gaus");
	cnv.Print("istogramma.png", "png");
	
	return 0;
}

