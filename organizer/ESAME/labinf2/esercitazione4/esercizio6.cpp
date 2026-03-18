//Questa funzione estrae una variabile xi aleatoria uniforme nell'intervallo [a,b], valuta yi=f(xi), ripete il procedimento N=10000 volte calcolando, al termine di ogni estrazione, la media e la varianza di y.

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <cmath>
 
#include "myLib.h"

int main()
{
 	srand(time(NULL));
	int N = 10000;
	
	double xMin = -5, xMax;
	
	std::cout << "Inserisci l'estremo superiore che si vuole utilizzare per calcolare l'integrale della pdf gaussiana: ";
	std::cin >> xMax;  	
	
	double somma = 0., somma_quadrati = 0., y;
	
	for (int i=0; i<N; i++)
	{
		y = MC_gaus(xMin, xMax);
		somma += y;
		somma_quadrati += y*y;
	}
	double media = somma / N;
	double varianza = somma_quadrati / N - media*media;
	
	varianza *= (double)N / (N-1.); 			//correzione del bias
	
	double errore_media = sqrt(varianza/N);
	double Integral = (xMax-xMin)*media;
	double errore_Integral = (xMax-xMin)*errore_media;
	
	std::cout << "Integrale della pdf gaussiana nel range ["<< xMin <<", " << xMax << "] = " << Integral 
		  << " +- " << errore_Integral << std::endl;
		  
	return 0;
 }
 
 
