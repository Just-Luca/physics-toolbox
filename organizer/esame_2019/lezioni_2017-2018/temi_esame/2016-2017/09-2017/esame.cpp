#include <iostream>
#include <cstdlib>
#include <TCanvas.h>
#include <TH1D.h>
#include <TApplication.h>
#include <TStyle.h>
#include <TF1.h>
#include <cmath>

#include "myLib.h"

int main()
{
	srand(time(NULL));
	int a = 0;
	int b = 1;
	int Nbins = 100;
	int max_num = 10000;

	//instanzio gli oggetti per creare l'interfaccia grafica per mostrare gli istogrammi
	gStyle -> SetOptFit(1112);
	TApplication* myApp = new TApplication ("myApp", NULL, NULL);
	TCanvas* myCanv = new TCanvas ("myCanv", "distribuzione uniforme", 0,0, 700, 500);
  
	//definisce un istogramma di 100 bin nell'intervallo (0,1)
	TH1D* myHisto = new TH1D("myHisto", "distribuzione uniforme", Nbins, a, b);

	for(int i=0; i<max_num; i++)
	{
		//genera 10000 numeri casuali secondo una pdf uniforme nell'intervallo (0,1)
		double numero_casuale = rand_range(a, b);
		
		//inserisce i numeri generati nell'istogramma
		myHisto->Fill(numero_casuale);		
	}

	//conta il numero di conteggi di ciascun bin e li salva in un vettore di interi
	int binContent[Nbins];
	std::cout << "Conteggi dei bin: " << std::endl;
	for(int i=0; i<Nbins; i++)
	{
		binContent[i] = myHisto -> GetBinContent(i+1);
		std::cout << "Bin " << i+1 << " : " << binContent[i] << std::endl;		
	}
	
	std::cout << "---------------------------------------------------------------------------------------" << std::endl;
	
	//stabilisce il range del nuovo istogramma
	int min = max_num/Nbins * 0.5;
	int max = max_num/Nbins * 1.5;

	TCanvas* myCanv2  = new TCanvas ("myCanv2", "distribuzione uniforme", 0, 0, 700, 500);
	TH1D* myHisto2 = new TH1D("myHisto2", "distribuzione binContent", 20, min, max);
	
	for(int i=0; i<Nbins; i++)
		myHisto2->Fill(binContent[i]);		
	
	//definisco una funzione gaussiana per fittare l'istogramma
	TF1* gaussian = new TF1 ("gaussian", "gaus", min, max);
	//fitto l'istogramma con la gaussiana
	myHisto2 -> Fit("gaussian");
	
	//valori attesi e stimati di media e deviazione standard.
	double mu_atteso = max_num/Nbins;
	double sigma_atteso = sqrt(mu_atteso);
	double mu_stimato = gaussian -> GetParameter(1);
	double errmu_stimato = gaussian -> GetParError(1);
	double sigma_stimato = gaussian -> GetParameter(2);
	double errsigma_stimato = gaussian -> GetParError(2);
	double pvalue1, pvalue2;

	//verifico la compatibilità tra media e deviazione standard attesi con quelli stimati
	if (testCompatibility(pvalue1, mu_stimato, errmu_stimato, mu_atteso, 0.05))
		std::cout << "il parametro mu è compatibile con il valore atteso entro un intervallo di confidenza del 95%" << std::endl;
	else
		std::cout << "il parametro mu non è compatibile con il valore atteso entro un intervallo di confidenza del 95%" << std::endl;

	if (testCompatibility(pvalue2, sigma_stimato, errsigma_stimato, sigma_atteso, 0.05))
		std::cout << "il parametro sigma è compatibile con il valore atteso entro un intervallo di confidenza del 95%" << std::endl;
	else
		std::cout << "il parametro sigma non è compatibile con il valore atteso entro un intervallo di confidenza del 95%" << std::endl;

	myCanv -> cd();
	myHisto -> Draw ();
	myCanv -> Modified();
	myCanv -> Update();
	
	myCanv2 -> cd();
	myHisto2 -> Draw ();
	myCanv2 -> Modified();
	myCanv2 -> Update();

	myApp -> Run();	
	return 0;
}

