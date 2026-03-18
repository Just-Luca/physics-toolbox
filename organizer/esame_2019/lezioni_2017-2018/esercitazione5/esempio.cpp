//Questo programma istanzia un istogramma come un tipo generico, lo riempie con numeri casuali e lo stampa a terminale

#include <iostream>
#include <iomanip>
#include <cmath>
#include <ctime>
#include <cstdlib>

#include "istogramma.h"
#include "myLib.h"

int main()
{
	srand(1);
	double a, b;
	std::cout << "Inserisci gli estremi dell'intervallo [a, b) in cui generare i numeri: ";
	std::cin >> a >> b;
	
	int N = 0;
	std::cout << "Inserisci quanti numeri casuali vuoi generare: ";
	std::cin >> N;
	
	//istanzio l'istogramma
	double min = 0;
	double max = 0;
	std::cout << "Inserisci gli estremi dell'istogramma [min, max): ";
	std::cin >> min >> max;
	
	int nBin = 0;
	std::cout << "Inserisci il numero di bin dell'istogramma: ";
	std::cin >> nBin;
	
	//costruttore
	istogramma myHisto(nBin, min, max);
	
	//riempio l'istogramma
	int estrazioni = 10;
	double random;
	for (int i=0; i<N; ++i)
	{
		random = rand_CLT (min, max, estrazioni);
		myHisto.Fill (random);
	}
	
	//stampo
	myHisto.Print();
	
	return 0;
}
		
	
