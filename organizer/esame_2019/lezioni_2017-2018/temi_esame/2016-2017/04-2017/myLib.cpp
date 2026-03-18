#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <fstream>
#include <TCanvas.h>
#include <TH1.h>
#include <TApplication.h>
#include <TStyle.h>
#include <TF1.h>
#include <cmath>

#include "myLib.h"


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


bool readData(const std::string filename, std::vector<double>& vectNum1, std::vector<double>& vectNum2, std::vector<double>& vectNum3)
{
	std::ifstream inFile(filename.c_str());
	
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
      	vectNum1.push_back(x);
      	vectNum2.push_back(y);
      	vectNum3.push_back(x/y);
	}
	
	inFile.close();
	return true;
}
