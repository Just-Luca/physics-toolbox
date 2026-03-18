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
#include <TStyle.h>
#include <TFitResult.h>
#include <TMatrixDSym.h>

using namespace std;

double fitfunc (double *x, double *p) {

	double arg = (x[0]-p[1])/p[2];
	double gaus = p[0]*exp(-0.5*arg*arg);
	double parab = p[3] + p[4]*x[0] + p[5]*x[0]*x[0];
	return gaus + parab;
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
	
	gStyle -> SetOptFit(1111);
	int nPar = 6;
	TF1 *f1 = new TF1 ("myFunz", fitfunc, min, max, nPar);
	f1->SetParameter(0, 10000); // normalizzazione gaussiana (valore massimo)
	f1->SetParameter(1, 5.); // valor medio della gaussiana
	f1->SetParameter(2, h1->GetRMS() ); 
	f1->SetParameter(3, 8500.); // intercetta della parabola
	
	h1->Fit("myFunz");
		
	double a = f1->GetParameter(5);
	double b = f1->GetParameter(4);
	double c = f1->GetParameter(3);
	cout << "Parametri della parabola: " << endl;
	cout << " a = " << a << " +- " << f1->GetParError(5) << endl;
	cout << " b = " << b << " +- " << f1->GetParError(4) << endl;
	cout << " c = " << c << " +- " << f1->GetParError(3) << endl;
	
	TF1 *f2 = new TF1 ("parabola","pol2", min, max);	
	f2->SetParameter(0, c);
	f2->SetParameter(1, b);
	f2->SetParameter(2, a);
	
	f2->SetLineColor(kBlue);
	f2->Draw("same");
	
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
 
	f2->Draw("same");
	
	myApp -> Run(); 
	return 0;
}



