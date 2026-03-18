// c++ -o FitHisto FitHisto.cpp `root-config --glibs --cflags`

// ./FitHisto data1.txt

#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <TApplication.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TF1.h>
#include <TH1D.h>
#include <TStyle.h>
#include <TFitResult.h>
#include <TMatrixDSym.h>
#include"myLib.h"

using namespace std;

double fitfunc (double *x, double *p) {

	return myExp(x,p) + myGauss(x,p+2) + myGauss(x,p+5);
}

int main (int argc, char **argv) {

	TApplication *myApp = new TApplication("app", 0, 0);
	
	ifstream in (argv[1]); 
	if (in.good()==false) {
		cout << "Errore apertura file" << endl;
		return 1;
	}
	
	double num, min, max;
	vector<double> ListNum;
	int Ndata=0;
	while (true) {
		in>>num;
		if (in.eof()==true) break;
		ListNum.push_back(num);
		if (Ndata == 0) {
			min=num;
			max=num;
		}
		else {
			if (num<min) min=num;
			if (num>max) max=num;
		}		
		Ndata++; 
	}
	cout << "Il file " << argv[1] << " contiene " << Ndata << " dati" << endl;
	cout << "Minimo: " << min << endl;
	cout << "Massimo: " << max << endl;
	
	
	int NBin = 100;
	TH1F *h1 = new TH1F ("h1","distribuzione dei dati", NBin, min, max);
	for (int i=0; i<Ndata; i++) {
		h1->Fill(ListNum[i]);
	}
	TCanvas *c1 = new TCanvas ();
	h1->Draw();
	
	h1->SetFillColor(kYellow);
	h1->GetXaxis() -> SetTitle("variabile x");
	h1->GetYaxis() -> SetTitle("conteggi");
	
	gStyle -> SetOptFit(1112);
	int nPar = 8;
	TF1 *f1 = new TF1 ("myFunz", fitfunc, min, max, nPar);
	f1->SetParameter(0, max); 
	f1->SetParameter(1, 10);
	
	f1->SetParameter(2, 1700); //valor massimo prima gaussiana
	f1->SetParameter(3, 135.); //valor medio prima gaussiana
	f1->SetParameter(4, h1->GetRMS());
	
	f1->SetParameter(5, 950); //valore massimo seconda gaussiana
	f1->SetParameter(6, 170.); //valor medio seconda gaussiana
	f1->SetParameter(7, h1->GetRMS()); 
	
	h1->Fit("myFunz");
		
	TFitResultPtr r = h1->Fit("myFunz", "S");
	r->Print("V");
	
	TMatrixDSym cov = r->GetCovarianceMatrix();
	cout << "\nMatrice di covarianza " << endl;
	for (int i=0; i<nPar; i++) {
		for (int j=0; j<nPar; j++) {
			double sigma_ij = cov(i,j);
			cout <<setw(15)<< sigma_ij;
		}
		cout << endl;
	}
	
	myApp -> Run(); 
	return 0;
}



