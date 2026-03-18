//Questo programma utilizza il metodo Hit or Miss per calcolare l'integrale di una pdf Normale con mu=0, sigma=1 in un generico range [-5, b].

#include <iostream>
#include <cstdlib>
#include <TCanvas.h>
#include <TH1F.h>
#include <cmath>

#include "myLib.h"

int main()
{
 	srand(time(NULL));
	int N = 100000;	
	int nHit = 0;
	
	double xMin = -5;
	double xMax = 1.;
	
	//std::cout << "Inserisci l'estremo superiore che si vuole utilizzare per calcolare l'integrale della pdf gaussiana: ";
	//std::cin >> xMax;	
	
	double yMin = 0., yMax = 1/sqrt(2*M_PI*1);
		
	for (int i=0; i<N; i++)
	{
		if (HitMiss_gaus(xMin, xMax, yMin, yMax)==true) 
			nHit++;
	}
	
	double Area = (xMax-xMin)*(yMax-yMin);
	double Integral = nHit*Area/(double)N;
	double p = nHit/(double)N;
	double Var = Area*Area/(double)N * p * (1.-p);
	double StdDev = sqrt(Var);
	
	std::cout << "Integrale della pdf gaussiana nel range [" << xMin << ", " << xMax <<"] = " << Integral 
		  << " +- "<< StdDev<< std::endl;
		  
	return 0;
 }
