#include <iostream>
#include <fstream>
#include <cmath>
//#include <iomanip>

#include <TApplication.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TF1.h>
#include <TStyle.h>
#include <TFitResult.h>
#include <TMatrixDSym.h>

using namespace std;

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
	
	myApp -> Run(); 
	
	return 0;
}
