//		c++ -o esame esame.cpp myLib.cpp `root-config --cflags --glibs`
//		./esame data_distr.txt

#include <iostream>
#include <fstream>

#include <TStyle.h>
#include <TApplication.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TF1.h>
#include <cmath>

#include "myLib.h"

int main(int argc, char** argv)
{
	int nBins   = 100;
	double xMin = 0;
	double xMax = 7;

	//verifica che il nome del file sia passato come argomento da riga di comando
	if (argc < 2)
	{
	    std::cout << "Insufficient number of parameters: ./esame data_distr.txt" << std::endl;
	    return -1;
	}

	TApplication *MyApp = new TApplication("MyApp", NULL, NULL);
	TCanvas* myCanv = new TCanvas("myCanv","myCanv", 0, 0, 700, 500);
	TH1F* myHisto = new TH1F("myHisto","myHisto", nBins, xMin, xMax);


	int nPar = 2;
	
	//definisce la prima funzione
	TF1* MyFun1 = new TF1("MyFun1", f1, xMin, xMax, nPar);
	MyFun1->SetParameter(0,1.);
	MyFun1->SetParameter(1,1.);

	//definisce la seconda funzione
	TF1* MyFun2 = new TF1("MyFun2", f2, xMin, xMax, nPar);
	MyFun2->SetParameter(0,1.);
	MyFun2->SetParameter(1,1.);
		
		
	//verifica che l'apertura e la lettura del file vadano a buon fine 
	if (ReadData(argv[1], myHisto) == false)
	{
		std::cout << "Error reading data file" << std::endl;
		return -1;
    }
    
    
	//fitto entrambe le funzioni nello stesso istogramma
	myHisto->Draw();
	myHisto->Fit("MyFun1","+");
	MyFun2->SetLineColor(kGreen);
	myHisto->Fit("MyFun2","+");
	
	myCanv->Modified();
	myCanv->Update();


	//calcolo del chi2 per f1
	std::cout << "Reduced Chi-2 f1: ";
	std::cout << MyFun1->GetChisquare()/MyFun1->GetNDF() << std::endl;

	double chi2_f1, NDF_f1;
	chi2_f1 = ComputeChi2(myHisto, MyFun1);	
	
	NDF_f1 = myHisto->GetNbinsX() - MyFun1->GetNpar();
	double reduced_chi2_f1 = chi2_f1/NDF_f1;
	std::cout << "My Chi-2 f1: " << chi2_f1 << std::endl;
  	std::cout << "My NDF f1: " << NDF_f1 << std::endl;
  	std::cout << "My Reduce Chi-2 f1: " << reduced_chi2_f1 << std::endl;
  	
  	//calcolo del chi2 per f2
  	std::cout << "Reduced Chi-2 f2: ";
	std::cout << MyFun2->GetChisquare()/MyFun2->GetNDF() << std::endl;

	double chi2_f2, NDF_f2;
	chi2_f2 = ComputeChi2(myHisto, MyFun2);
	
	NDF_f2 = myHisto->GetNbinsX() - MyFun2->GetNpar();
	double reduced_chi2_f2 = chi2_f2/NDF_f2;
	std::cout << "My Chi-2 f2: " << chi2_f2 << std::endl;
  	std::cout << "My NDF f2: " << NDF_f2 << std::endl;
  	std::cout << "My Reduce Chi-2 f2: " << reduced_chi2_f2 << std::endl;
  		
	MyApp->Run();
	
	return 0;
}

