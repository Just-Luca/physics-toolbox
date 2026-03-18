#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <math.h>
#include <vector>
#include <TMath.h>

#include "misura.h"

#include <iomanip>

//default constructor
misura::misura()
{
	std::cout << "Inserire la misura: " << std::endl;
	std::cin >> X_p;
	std::cout << "Inserire l'errore: " << std::endl;
	std::cin >> EX_p;
}

//constructor
misura::misura(const string& filename)
{
	vector<double> data;
	double x;

  	X_p = 0;
  	EX_p = 0;

	std::ifstream inFile(filename.c_str());
	if(! inFile.good())
    	std::cout << "ERRORE: impossibile aprire il file " << filename << std::endl;
    else
    {
		while (true)
		{
			inFile >> x;
			if (inFile.eof()) break;
			data.push_back(x);
				X_p += x;
		}
    
		X_p = X_p*1.e8/ (double)(data.size());
    
		double somma_quadrati = 0;
		for (int i=0; i<data.size(); i++)
    		somma_quadrati += pow(data[i]*1.e8 - X_p, 2);

		double varianza = somma_quadrati / (double)(data.size()-1);
		double dev_std = sqrt(varianza);
		EX_p = dev_std / (double)(sqrt(data.size()));
		
		std::cout << std::setprecision(16); 
		std::cout << "\nStima delle misure del file: " << X_p << " +/- " << EX_p << std::endl;
	}
}

//destructor
misura::~misura() {}

/***********************************************************************************************************/

//metodo somma
void misura::Somma (const misura& other)
{
	double Xs, errXs;
	Xs = X_p + other.X_p;
	errXs = sqrt(pow(EX_p, 2) + pow(other.EX_p, 2));

	std::cout << "Somma = " << Xs << " +/- " << errXs << std::endl;
}

//metodo prodotto
void misura::Moltiplica (const misura& other)
{
	double X, errX;
	X = X_p * other.X_p;
	errX = sqrt(pow((other.X_p*EX_p), 2) + pow(X_p*other.EX_p, 2));

	std::cout << "Prodotto = " << X << " +/- " << errX << std::endl;
}

//metodo confronta
void misura::Confronta (const misura& other) const
{
	double t, prob;
  
	t = fabs(this->X_p - other.X_p) / sqrt(pow(this->EX_p, 2) + pow(other.EX_p, 2));
	prob = TMath::Erfc(t/sqrt(2.));

	if (prob > 0.05)
		std::cout << "le misure sono compatibili in un intervallo di confidenza del 95%" << std::endl;
	else
		std::cout << "le misure non sono compatibili in un intervallo di confidenza del 95%" << std::endl;
}

