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

double dist1 (double *E, double *p) {
	
	return p[0]*pow(E[0],2)*exp(-p[1]*E[0]);
}

double dist2 (double *E, double *p) {

	return p[0]*E[0]*exp(-p[1]*E[0]);
}

double dist3 (double *E, double *p) {

	return p[0]*pow(E[0],2)*exp(-p[1]*pow(E[0],2));
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

	int nPar = 2;
	TF1 *f1 = new TF1 ("myFunz1", dist1, min, max, nPar);
	f1->SetParameter(0, 1.); 
	f1->SetParameter(1, 1.);
	
	h1->Fit("myFunz1","+");
	
	TF1 *f2 = new TF1 ("myFunz2", dist2, min, max, nPar);	
	f2->SetParameter(0, 1.);
	f2->SetParameter(1, 1.);
	
	f2->SetLineColor(kBlue);
	h1->Fit("myFunz2","+");
	
	TF1 *f3 = new TF1 ("myFunz3", dist3, min, max, nPar);	
	f3->SetParameter(0, 1.);
	f3->SetParameter(1, 1.);
	
	f3->SetLineColor(kGreen);
	h1->Fit("myFunz3","+");
	
	TFitResultPtr r = h1->Fit("myFunz2", "S");
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
