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

int main (int argc, char** argv) {

	if (argc < 3) { // verifico che vengano passati almeno due parametri da riga 
	
		std::cout << "Digitare il nome dei file da riga di comando!\n";
		return 1;
	}
	
	std::ifstream InA (argv[1]);
	std::ifstream InB (argv[2]);
	
	if (InA.good() == 0 || InB.good() == 0 ) {
	
		std::cout << "Errore! Non è possibile aprire i file." << std::endl;
		return 1;
	}
	
	dataset A (argv[1]);
	dataset B (argv[2]);
	
	TApplication *myApp = new TApplication("app", 0, 0);
	gStyle -> SetOptFit(1112);
	
	TCanvas *c1 = new TCanvas ("c1", "My Canvas");
	c1->Divide(2,1);
	
	ifstream inA (argv[1]); 
	if (inA.good()==false) {
	
		cout << "Errore apertura file " << argv[1] << endl;
		return 1; 
	}
	
	int min = 0;
	int max = (int) 10*A.GetDevstd();
	int NBin = max;
	
	
	
	TH1F *h1 = new TH1F ("h1","distribuzione dei dati A", NBin, min, max);
	
	int N = 0;
	
	for (int i = 0; i < A.GetNdati(); i++) {
	
		N = A.GetDato(i);
		h1->Fill(N);
	}
	
	c1->cd(1);
	h1->Draw();
	
	h1->SetFillColor(kYellow);
	h1->GetXaxis() -> SetTitle("variabile x");
	h1->GetYaxis() -> SetTitle("conteggi");
	
	h1->Fit("gaus");
	
	ifstream inB (argv[2]); 
	if (inB.good()==false) {
	
		cout << "Errore apertura file " << argv[2] << endl;
		return 1;
	}
	
	min = 0;
	max = (int) 10*B.GetDevstd();
	NBin = max;
	
	TH1F *h2 = new TH1F ("h2","distribuzione dei dati B", NBin, min, max);
	
	N = 0;
	
	for (int t = 0; t < B.GetNdati(); t++) {
	
		N = B.GetDato(t);
		h2->Fill(N);
	}
	
	c1->cd(2);
	h2->Draw();
	
	h2->SetFillColor(kGreen);
	h2->GetXaxis() -> SetTitle("variabile x");
	h2->GetYaxis() -> SetTitle("conteggi");

	h2->Fit("gaus");
	
	/*c1->Modified();
	c1->Update();*/
		
	myApp -> Run();
	
	return 0;
}
