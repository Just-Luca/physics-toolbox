#include <iostream>
#include <vector>
#include <TApplication.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TF1.h>
#include <TStyle.h>

#include "myLib.h"

int main(int argc, char** argv)
{
	std::vector<double> vectNum;
	//lettura da file, riempimento di un vector e verifica che le operazioni vadano a buon fine
	bool lettura = readData("energy_distr.txt", vectNum);
	if(lettura == false)
	{
		std::cout << "Errore lettura file" << std::endl;
		return -1;
	}
	
	//oggetti necessari per visualizzare l'istogramma
	TApplication* myApp = new TApplication("myApp", 0, 0);
	TCanvas* myCanv = new TCanvas("myCanv","myCanv",0,0,700,500);
	TH1F* myHisto = new TH1F ("myHisto","distribuzione dei dati", 1000, 0, 10);
	
	//riempie l'istogramma
	for (int i=0; i<vectNum.size(); i++)
		myHisto->Fill(vectNum[i]);

	myHisto->Draw();
	
	myHisto->SetFillColor(kYellow);
	myHisto->GetXaxis() -> SetTitle("variabile x");
	myHisto->GetYaxis() -> SetTitle("conteggi");
	
	gStyle -> SetOptFit(1112);
	//Fitto la prima funzione
	TF1* dist1 = new TF1("dist1", fun1, 0, 10, 1);
	dist1->SetParameter(0, 1000);
	
	//fitto la seconda funzione
	TF1* dist2 = new TF1("dist2", fun2, 0, 10, 2);
	dist2->SetParameter(0, 1728);
	dist2->SetParameter(1, 1.342);
	dist2->SetLineColor(kGreen);
	
	//fitto la terza funzione
	TF1* dist3 = new TF1("dist3", fun3, 0, 10, 3);
	dist3->SetParameter(0, 2.67e+8);
	dist3->SetParameter(1, 35.11);
	dist3->SetParameter(2, 7.179);
	dist3->SetLineColor(kWhite);
	
	myHisto->Draw();

	myHisto->Fit("dist1", "+");
	myHisto->Fit("dist2", "+");
	myHisto->Fit("dist3", "+");
	
	//calcolo del chi2 per f1
	std::cout << "\nChi-2 f1: ";
	std::cout << dist1->GetChisquare() << std::endl;
	std::cout << "Reduced Chi-2 f1: ";
	std::cout << dist1->GetChisquare()/dist1->GetNDF() << std::endl;
	std::cout << "NDF f1: " << dist1->GetNDF() << std::endl;

	double chi2_f1, NDF_f1;
	chi2_f1 = computeChi2(myHisto, dist1);
	
	int bin_nonnulli1 = 0;
	for(int i=1; i <= (myHisto->GetNbinsX()); i++)
		if(myHisto->GetBinContent(i) > 0)		
			++bin_nonnulli1;
			
	NDF_f1 = bin_nonnulli1 - dist1->GetNpar();	
	double reduced_chi2_f1 = chi2_f1/NDF_f1;
	
	std::cout << "My Chi-2 f1: " << chi2_f1 << std::endl;
  	std::cout << "My NDF f1: " << NDF_f1 << std::endl;
  	std::cout << "My Reduce Chi-2 f1: " << reduced_chi2_f1 << std::endl;
  	
  	//calcolo del chi2 per f2
	std::cout << "\nChi-2 f2: ";
	std::cout << dist2->GetChisquare() << std::endl;
	std::cout << "Reduced Chi-2 f2: ";
	std::cout << dist2->GetChisquare()/dist2->GetNDF() << std::endl;
	std::cout << "NDF f2: " << dist2->GetNDF() << std::endl;

	double chi2_f2, NDF_f2;
	chi2_f2 = computeChi2(myHisto, dist2);
	
	int bin_nonnulli2 = 0;
	for(int i=1; i <= (myHisto->GetNbinsX()); i++)
		if(myHisto->GetBinContent(i) > 0)		
			++bin_nonnulli2;
			
	NDF_f2 = bin_nonnulli2 - dist2->GetNpar();	
	double reduced_chi2_f2 = chi2_f2/NDF_f2;
	
	std::cout << "My Chi-2 f2: " << chi2_f2 << std::endl;
  	std::cout << "My NDF f2: " << NDF_f2 << std::endl;
  	std::cout << "My Reduce Chi-2 f2: " << reduced_chi2_f2 << std::endl;
  	
  	//calcolo del chi2 per f3
	std::cout << "\nChi-2 f3: ";
	std::cout << dist3->GetChisquare() << std::endl;
	std::cout << "Reduced Chi-2 f3: ";
	std::cout << dist3->GetChisquare()/dist3->GetNDF() << std::endl;
	std::cout << "NDF f3: " << dist3->GetNDF() << std::endl;

	double chi2_f3, NDF_f3;
	chi2_f3 = computeChi2(myHisto, dist3);
	
	int bin_nonnulli3 = 0;
	for(int i=1; i <= (myHisto->GetNbinsX()); i++)
		if(myHisto->GetBinContent(i) > 0)		
			++bin_nonnulli3;
			
	NDF_f3 = bin_nonnulli3 - dist3->GetNpar();	
	double reduced_chi2_f3 = chi2_f3/NDF_f3;
	
	std::cout << "My Chi-2 f3: " << chi2_f3 << std::endl;
  	std::cout << "My NDF f3: " << NDF_f3 << std::endl;
  	std::cout << "My Reduce Chi-2 f3: " << reduced_chi2_f3 << std::endl;
  	
  	
  	std::cout << "\nLa funzione che meglio si adatta alle misure è f1" << std::endl;
  	
	myCanv->Modified();
	myCanv->Update();
	
	myApp->Run();
	
	return 0;
}
