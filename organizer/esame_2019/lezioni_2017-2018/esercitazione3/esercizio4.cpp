//Questo programma utilizza la funzione rand_FCI_exp per generare N numeri casuali secondo la pdf esponenziale. Ripete l'operazione 10000 volte in un ciclo calcolando per ogni coppia il valor medio. Riempie un istogramma TH1F con 100 bin per rappresentare la distribuzione di probabilità dei valori medi calcolati. 

#include <iostream>
#include <cstdlib>
#include <TCanvas.h>
#include <TH1F.h>

#include "myLib.h"

int main()
{
	srand(time(NULL));
	int max_num = 10000;
    double mu = 0.25;
	double dati[max_num];
	int N=0;
	std::cout << "Inserire il numero di dati di cui si vuole calcolare la media: ";
	std::cin >> N;
	
	double n_media[N];

	TH1F myHisto("distribuzione_FCI", "istogramma", 100, 0, 1);
	
	for(int i=0; i<max_num; i++)
	{	
		for(int j=0; j<N; j++)
			n_media[j] = rand_FCI_exp(mu);
		
		dati[i] = media(n_media, N);
	}

	for(int i=0; i<max_num; i++)
		myHisto.Fill(dati[i]);
	TCanvas cnv;
	myHisto.Draw();
	myHisto.Fit("gaus");
	cnv.Print("istogramma.png", "png");

	return 0;
}

