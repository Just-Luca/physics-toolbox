//Questo programma amplia la classe istogramma inserendo metodi per calcolare la media, la deviazione standard, l'integrale, il numero di contaggi al di sopra del valore massimo e quelli al di sotto del valore minimo.

#include <iostream>
#include <iomanip>
#include <cmath>
#include <ctime>
#include <cstdlib>

#include "istogramma.h"
#include "myLib.h"

int main()
{
 	srand (time (NULL));
  
	float a = 0.;
	float b = 1.;
	std::cout << "Inserisci gli estremi dell'intervallo [a,b) in cui generare i numeri: ";
	std::cin >> a >> b;
  
	int numeri = 0;
	std::cout << "Inserisci quanti numeri casuali vuoi generare: ";
	std::cin >> numeri;
  
 	//creo l'istogramma
  	float min = 0.;
  	float max = 1.;
  	std::cout << "Inserisci gli estremi dell'istogramma [min,max): ";
  	std::cin >> min >> max;

  	int nBin = 0;
  	std::cout << "Inserisci il numero di bin dell'istogramma: ";
  	std::cin >> nBin;
  
  	//constructor
  	istogramma myHisto(nBin, min, max);
  
  	//riempio l'istogramma
  	for(int i = 0; i < numeri; ++i)
  	{
    	float number = rand_range(a, b);
    	myHisto.Fill(number);
  	}

  	//stampo 
  	std::cout << "Mean = " << myHisto.GetMean() << std::endl; 
  	std::cout << "RMS  = " << myHisto.GetRMS() << std::endl; 
  	std::cout << "overflow  = " << myHisto.GetOverflow() << std::endl; 
  	std::cout << "underflow = " << myHisto.GetUnderflow() << std::endl; 
  	std::cout << "max counts = " << myHisto.GetMax() << std::endl; 
  	std::cout << "integral [" << min << ", " << max << "] = " << myHisto.GetIntegral() << std::endl; 
  
  	std::cout << "Bin Center Content" << std::endl; 
  	for (int i=0; i<nBin; i++) {
  	std::cout << i << "\t" << myHisto.GetBinCenter(i) << "\t" << myHisto.GetBinContent(i) << std::endl; 	
  }
  myHisto.Print();
  
  return 0;
}

