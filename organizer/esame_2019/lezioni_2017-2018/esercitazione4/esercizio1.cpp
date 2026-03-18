//Questo programma estrae M=10000 numeri casuali da una distribuzione uniforme nel range [a, b] e calcola la media dei numeri estratti. Ripete la procedura per 1000 volte e inserisce i valori medi in un istogramma TH1F. Calcola la media e la deviazione standard dei valori medi ricavati nelle 1000 ripetizioni.

#include <iostream>
#include <cstdlib>
#include <TCanvas.h>
#include <TH1F.h>
#include <cmath>

#include "myLib.h"
#define M 10000

int main()
{
	srand(time(NULL));
	int max_num = 1000;
	double dati[max_num];
	int a, b;
	double MEDIA = 0;
	double VARIANZA = 0;
	double deviazione = 0;
	std::cout << "Inserisci il valore minimo: ";
	std::cin >> a;
	std::cout << "Inserisci il valore massimo: ";
	std::cin >> b;

	double n_media[M];

	TH1F myHisto("distribuzione_uniforme", "istogramma", 100, a, b);
	
	for(int i=0; i<max_num; i++)
	{	
		for(int j=0; j<M; j++)
			n_media[j] = rand_range(a, b);
		
		dati[i] = media(n_media, M);
		myHisto.Fill(dati[i]);
	}
	
	MEDIA = media(dati, M);
	VARIANZA = varianza(dati, MEDIA, M);
	deviazione = sqrt(VARIANZA);

	std::cout << "La media dei valori medi delle 1000 ripetizioni è: " << MEDIA << std::endl;
	std::cout << "La deviazione standard dei valori medi delle 1000 ripetizioni è: " << deviazione << std::endl;
	
	TCanvas cnv;
	myHisto.Draw();
	myHisto.Fit("gaus");
	cnv.Print("istogramma.png", "png");

	return 0;
}

