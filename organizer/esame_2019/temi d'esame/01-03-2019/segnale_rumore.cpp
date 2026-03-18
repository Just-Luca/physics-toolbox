#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>	
#include <cstdlib>
#include <vector>
#include <string>

#include <TApplication.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TF1.h>
#include <TStyle.h>
#include <TFitResult.h>
#include <TMatrixDSym.h>
#include <TGraphErrors.h>
#include <TAxis.h>

#include "dataset.h"

double funzione (double* x, double* par) {

	double val = par[0]*pow(x[0],2) + par[1]*x[0] + par[2]; 
	return val;
}

void ComputeChi2(TGraphErrors* myData, TF1* myFun, double& chi2, double& NDF) {
	
	double result = 0;

	for (int i = 0; i < myData->GetN(); i++) {
	
      	result += pow(myData->GetY()[i] - myFun->Eval(myData->GetX()[i]),2.) /
(pow(myFun->Derivative(myData->GetX()[i])*myData->GetErrorX(i),2.));
	}
  
	chi2 = result;
	NDF  = myData->GetN() - myFun->GetNpar();
}

int main (int argc, char** argv) {

	if (argc < 3) { // verifico che vengano passati almeno due parametri da riga 
	
		std::cout << "Digitare il nome dei file da riga di comando!\n";
		return 1;
	}
	
	std::ifstream InSignal (argv[1]);
	std::ifstream InNoise (argv[2]);
	
	if (InSignal.good() == 0 || InNoise.good() == 0 ) {
	
		std::cout << "Errore! Non è possibile aprire i file." << std::endl;
		return 1;
	}
	
	dataset Signal (argv[1]);
	dataset Noise (argv[2]);
	
	TApplication *myApp = new TApplication("app", 0, 0);
	gStyle -> SetOptFit(1112);
	
	TCanvas *c1 = new TCanvas ("c1", "Spettri Signal - Noise");
	c1->Divide(2,1);
	
	ifstream inSignal (argv[1]); 
	if (inSignal.good()==false) {
	
		cout << "Errore apertura file " << argv[1] << endl;
		return 1; 
	}
	
	int min = (int) Signal.GetMin();
	int max = (int) Signal.GetMax();
	int nBin = max-min;
	 
	TH1F *h1 = new TH1F ("hSignal","distribuzione dei dati Signal", nBin, min, max);
	
	int N = 0;
	
	for (int i = 0; i < Signal.GetNdati(); i++) {
	
		N = Signal.GetDato(i);
		h1->Fill(N);
	}
	
	c1->cd(1);
	h1->Draw();
	
	h1->SetFillColor(kYellow);
	h1->Draw("E same");
	
	h1->GetXaxis() -> SetTitle("energia del segnale");
	h1->GetYaxis() -> SetTitle("conteggi");
	
	//h1->Fit("gaus");*/
	
	ifstream inNoise (argv[2]); 
	if (inNoise.good()==false) {
	
		cout << "Errore apertura file " << argv[2] << endl;
		return 1;
	}
	
	TH1F *h2 = new TH1F ("hNoise","distribuzione dei dati Noise", nBin, min, max);
	
	N = 0;
	
	for (int t = 0; t < Noise.GetNdati(); t++) {
	
		N = Noise.GetDato(t);
		h2->Fill(N);
	}
	
	c1->cd(2);
	h2->Draw();
	
	h2->SetFillColor(kGreen);
	h2->Draw("E same");
	
	h2->GetXaxis() -> SetTitle("energia del rumore");
	h2->GetYaxis() -> SetTitle("conteggi");

	//h2->Fit("gaus");
	
	c1->Modified();
	c1->Update();

/*	
	int A = h1->GetBinContent(25);	
	int B = h2->GetBinContent(25);		
	std::cout << "Il "<< 25 << "° bin di h1 è largo " << A << std::endl;
	std::cout << "Il "<< 25 << "° bin di h2 è largo " << B << std::endl;
	std::cout << "devst: " << Signal.GetDevstd() << std::endl;
*/
	
/*		
	//controllo che per ogni bin di hSignal valga l'approssimazione gaussiana
	
	int r = 1;
	int B = 0;
	
	while (r < nBin) {
	
		B = h1->GetBinContent(r);
	
		if (B < 10) {
			
			std::cout << "Il "<< r << "° bin contiene meno di 10 conteggi" << 			std::endl;
			break;
		}	
		
		else continue;
		
		r++;
	}

	//controllo che per ogni bin di hNoise valga l'approssimazione gaussiana

	int u = 1;
	int C = 0;
	
	while (u < nBin) {
	
		C = h2->GetBinContent(u);
		
		if (C < 10) {
			
			std::cout << "Il "<< u << "° bin contiene meno di 10 conteggi" << 			std::endl;
			break;
		}	
		
		else continue;
		
		u++;
	}	
*/		

//	TApplication *myApp = new TApplication("app", 0, 0);
//	gStyle -> SetOptFit(1112);
	
	TCanvas *c2 = new TCanvas ("c2", "Rapporto Segnal/Noise");

	double x,y;
	int nPoints = nBin;
	double errX = 0;
	double errY;
	
	TGraphErrors* myGraph = new TGraphErrors();
	
	for (int l = 1; l < nBin +1; l++) {
		
		double S = h1->GetBinContent(l);
		double N = h2->GetBinContent(l);
		double N_2 = pow(N,-2);
		double errS = h1->GetBinError(l);
		double errN = h2->GetBinError(l);
		
		x = h1->GetBinCenter(l);
		y = S/N;
		errY = sqrt(pow(errS/N,2) + pow((S*errN)/N_2,2));
		
		myGraph->SetPoint(myGraph->GetN(),x,y);
		myGraph->SetPointError(myGraph->GetN()-1,errX,errY);
	}
	
	myGraph->Draw("AP");
	myGraph->SetMarkerStyle(20);
	myGraph->SetMarkerSize(0.2);
	myGraph->GetXaxis()->SetTitle("energia media del bin");
	myGraph->GetYaxis()->SetTitle("rapporto Signal/Noise");
	
	TF1* myFun = new TF1("myFun", funzione, min, max, 3);
	myFun->SetParameter(0, 1);
	myFun->SetParameter(1, -30);
	myFun->SetParameter(2, -3000);
	
	myFun->SetParName(0, "a");
	myFun->SetParName(1, "b");
	myFun->SetParName(2, "c");

 	myGraph->Fit("myFun");	
 	
 	c2->cd();
	c2->Modified();
	c2->Update();

/*	gStyle->SetOptFit(1112);
	TApplication* myApp = new TApplication("myApp", NULL, NULL);
	TCanvas* myC = new TCanvas("myC","myC",0,0,700,500);
	
	TGraphErrors* myGraph = new TGraphErrors(argv[1]);
	myGraph->SetMarkerStyle(20);
	myGraph->SetMarkerSize(0.2);
	myGraph->GetXaxis()->SetTitle("Titolo x");
	myGraph->GetYaxis()->SetTitle("Titolo y");

	TF1* myFun = new TF1("myFun", funzione, min, max, 3);
	myFun->SetParameter(0, 1);
	myFun->SetParameter(1, 1);
	myFun->SetParameter(2, 1);
	
	myFun->SetParName(0, "a");
	myFun->SetParName(1, "b");
	myFun->SetParName(2, "c");

	myC->cd();
	myGraph->Draw("AP");
 	myGraph->Fit("myFun");	
	myC->Modified();
	myC->Update();

	std::cout << "Reduced Chi-2: ";
	std::cout << myFun->GetChisquare()/myFun->GetNDF() << std::endl;
	std::cout << "p-value: " << myFun->GetProb() << std::endl;

	double chi2, NDF;
	ComputeChi2(myGraph,myFun,chi2,NDF);
	std::cout << "My Chi-2: " << chi2 << std::endl;
	std::cout << "My NDF: " << NDF << std::endl;
	
	myC->Print("V"); 
*/
	
	myApp -> Run();
	
	return 0;
}
