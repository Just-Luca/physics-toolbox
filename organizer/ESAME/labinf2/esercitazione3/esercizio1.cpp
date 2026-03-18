//Questa funzione genera N=10^4 numeri casuali distribuiti uniformemente nell'intervallo [a,b], stima la media e la varianza del campione di numeri random generati e definisce e riempie un istogramma TH1F con 100 bin.

#include <iostream>
#include <cstdlib>
#include "myLib.h"
#include <TCanvas.h>
#include <TH1F.h>

int main()
{
	srand(time(NULL));
	double a, b;
	double somma = 0;
	double sommaquadrati = 0;
	int max_num = 10000;
	int n_estrazioni;

	std::cout << "Inserisci il valore minimo: " << std::endl;
	std::cin >> a;
	std::cout << "Inserisci il valore massimo: " << std::endl;
	std::cin >> b;

	TH1F myHisto("distribuzione_uniforme", "istogramma", 100, a, b);

	for(int i=0; i<max_num; i++)
	{
		double numero_casuale = rand_range(a, b);
		somma += numero_casuale;
		sommaquadrati += numero_casuale * numero_casuale;

		myHisto.Fill(numero_casuale);		
	}

	double media = somma/max_num;
	double varianza = sommaquadrati/max_num - media * media;
	std::cout << "La media dei valori è: " << media << std::endl;
	std::cout << "La varianza dei valori è: " << varianza << std::endl;

	TCanvas cnv;
	myHisto.Draw();
	myHisto.Fit("gaus");
	cnv.Print("istogramma.png", "png");
	
	return 0;
}

