#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>

#include "myLib.h"

bool readData(std::string fileName, std::vector<double>& valVec, std::vector<double>& errVec)
{
	std::ifstream inFile(fileName.c_str());
	
	//verifica che l'apertura del file vada a buon fine
	if (inFile.good()==false)
	{
		std::cout << "Errore apertura file" << std::endl;
		return false;
	}
	
	//riempie due vector con i dati del file
	double x = 0;
	double y = 0;
	
	while (inFile.eof()==false)
    	{
    		inFile >> x >> y;
      		valVec.push_back(x);
      		errVec.push_back(y);
	}
	
	inFile.close();
	return true;
}

/*************************************************************************************************/

double computeAvg(std::vector<double>& valVec)
{
	double somma = 0;
	for(int i=0; i<valVec.size(); i++)
		somma += valVec[i];

	double media = somma/valVec.size();
	std::cout << "\nLa media delle misure presenti nel file è: " << media << std::endl;
	
	return media; 
}

/*************************************************************************************************/

double myGauss(double* x, double* par)
{
	return par[0]*exp(-0.5*(pow((x[0]-par[1])/par[2], 2)));
}

