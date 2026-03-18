#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <string>
#include <TH1.h>
#include <TF1.h>

//#include <algorithm>

#include "myLib.h"

#define PI 3.14159


double computeChi2(TH1F* myHisto, TF1* myFun)
{
	double chi_quadro = 0;
	for(int i=1; i <= (myHisto->GetNbinsX()); i++)
		if(myHisto->GetBinContent(i) > 0)
			chi_quadro += pow((myHisto->GetBinContent(i) - myFun->Eval(myHisto->GetBinCenter(i))), 2.) / myHisto->GetBinContent(i);
		//chi_quadro = std::min(chi_quadro, myHisto->GetBinContent(i));
		
  	return chi_quadro;
	//NDF  = myHisto->GetNbinsX() - myFun->GetNpar();
}


double fun1(double* x, double* par)
{
	return (par[0]/sqrt(PI)) * sqrt(x[0]) * exp(-x[0]);
}


double fun2(double* x, double* par)
{
	return par[0] * x[0] * exp(par[1]*x[0]);
}


double fun3(double* x, double* par)
{
	return par[0] * x[0] * exp(-2*x[0]) * exp( -pow((x[0]-par[1]),2) / (2*par[2]*par[2]) );
}


bool readData(const std::string filename, std::vector<double>& vectNum)
{
	std::ifstream inFile(filename.c_str());
	
	//verifica che l'apertura del file vada a buon fine
	if (inFile.good()==false)
	{
		std::cout << "Errore apertura file" << std::endl;
		return false;
	}
	
	//riempie un vector con i dati del file
	double num;
	
	while (inFile.eof()==false)
    {
    	inFile >> num;
      	vectNum.push_back(num);
	}
	
	inFile.close();
	return true;
}

