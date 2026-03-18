#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <fstream>
#include <TH1.h>
#include <TF1.h>

#include "myLib.h"


double ComputeChi2(TH1F* myHisto, TF1* myFun)
{
	double chi_quadro = 0;
	for(int i=1; i <= (myHisto->GetNbinsX()); i++)
		chi_quadro += pow((myHisto->GetBinContent(i) - myFun->Eval(myHisto->GetBinCenter(i))),2.) / myHisto->GetBinContent(i);
		
  	return chi_quadro;
	//NDF  = myHisto->GetNbinsX() - myFun->GetNpar();
}


double f1(double* x, double* par)
{
	return par[0] * sqrt(x[0]) * exp(-par[1]*x[0]);
}


double f2(double* x, double* par)
{
	return par[0] * x[0] * exp(-par[1]*x[0]);
}


bool ReadData(char* fileName, TH1F* myHisto)
{
	double val;
	std::fstream f;
	f.open(fileName,std::ios::in);
	
	if (f.good() == false)
		return false;
	while (true)
	{
		f >> val;
		if (f.eof() == true) break;
		myHisto->Fill(val);
    }
	return true;
}

