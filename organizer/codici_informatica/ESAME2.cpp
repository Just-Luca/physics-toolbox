/*
c++ -o ESAME ESAME.cpp `root-config --cflags --glibs`
*/

//INSERIRE IL FILE DA TERMINALE

#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>

#include <TApplication.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TF1.h>
#include <TStyle.h>


//funzione che mi restituisce il chi-quadro e i gradi di libertà

void ComputeChi2(TH1D* myHisto, TF1* myFun, double &chi2, double &NDF) {

	double result = 0;
	
	for (unsigned int i = 1; i <= myHisto->GetNbinsX(); i++) {
	
      	result += pow((myHisto->GetBinContent(i) - myFun->Eval(myHisto->GetBinCenter(i))),2.) / myHisto->GetBinContent(i);
	}

	chi2 = result;
	NDF  = myHisto->GetNbinsX() - myFun->GetNpar();
}

using namespace std;

//distribuzione gaussiana
double dist1 (double *x, double *p) {
	
	return p[0]*exp(pow((x[0]-p[1]),2)/-2*p[2]*p[2]);
}

//distribuzione di Cauchy
double dist2 (double *x, double *p) {

	return p[0]/(pow((x[0]-p[1]),2) + p[2]*p[2]);
}

int main (int argc, char **argv) {


	TApplication *myApp = new TApplication("app", 0, 0);
	
	//controllo che il file venga aperto correttamente
	ifstream in (argv[1]); 
	if (in.good() == false) {
		cout << "Errore apertura file" << endl;
		return 1;
	}

	double num, min, max;
	vector<double> ListNum;
	int Ndata = 0;
	while (true) {
	
		in >> num;
		if (in.eof() == true) break;
		ListNum.push_back(num);
		if (Ndata == 0) {
			min = num;
			max = num;
		}
		else {
			if (num < min) min = num;
			if (num > max) max = num;
		}
				
		Ndata++; 
	}
	
	cout << "Il file " << argv[1] << " contiene " << Ndata << " dati" << endl;
	cout << "Minimo: " << min << endl;
	cout << "Massimo: " << max << endl;
	

	//riempio l'istogramma h1
	int NBin = 100;
	TH1D *h1 = new TH1D ("h1","distribuzione dei dati", NBin, min, max);
	for (int i=0; i<Ndata; i++) {
		h1->Fill(ListNum[i]);
	}
	
	TCanvas *c1 = new TCanvas ();
	h1->Draw();
	h1->SetFillColor(kYellow);
	h1->GetXaxis() -> SetTitle("variabile x");
	h1->GetYaxis() -> SetTitle("conteggi");
	
	gStyle -> SetOptFit(1112);

	int nPar = 3;
	TF1 *f1 = new TF1 ("Gaus", dist1, -10, 10, nPar);
	f1->SetParameter(0, 700.); 
	f1->SetParameter(1, 1.);
	f1->SetParameter(2, 1.);
	
	TF1 *f2 = new TF1 ("Cauchy", dist2, min, max, nPar);	
	f2->SetParameter(0, 600.);
	f2->SetParameter(1, 1.);
	f2->SetParameter(2, 1.);
	
	
	f2->SetLineColor(kBlue);
	h1->Fit("Cauchy","+");

	h1->Fit("Gaus","+");

	double chi2G, chi2C; 
	double NDFG, NDFC;

	ComputeChi2(h1, f1, chi2G, NDFG);
	ComputeChi2(h1, f2, chi2C, NDFC);

	cout << "\t" << endl;

	cout << "My chi2G: " << chi2G << endl;
	cout << "My NDFG: " << NDFG << endl;
	cout << "My reduced-chi2G: " << chi2G/NDFG << endl;
	
	cout << "My chi2C: " << chi2C << endl;
	cout << "My NDFC: " << NDFC << endl;
	cout << "My reduced-chi2C: " << chi2C/NDFC << endl;

	if (abs(1-chi2C/NDFC) < abs(1-chi2G/NDFG)) {

		cout << "La funzione che meglio si adatta ai dati è dist2." << endl;
	} 

	else { cout << "La funzione che meglio si adatta ai dati è dist1." << endl; 	
	}

	cout << "\t" << endl;
	
	cout << "ROOT Reduced Chi-2G: ";
	cout << f1->GetChisquare()/f1->GetNDF() << std::endl;
	cout << "ROOT p-valueG: " << f1->GetProb() << std::endl;

	cout << "ROOT Reduced Chi-2C: ";
	cout << f2->GetChisquare()/f2->GetNDF() << std::endl;
	cout << "ROOT p-valueC: " << f2->GetProb() << std::endl;

	double A = f1->GetChisquare()/f1->GetNDF();
	double B = f2->GetChisquare()/f2->GetNDF();

	if (abs(1-B) < abs(1-A)) {

		cout << "ROOT: la funzione che meglio si adatta ai dati è dist2." << endl;
	} 

	else { cout << "ROOT: la funzione che meglio si adatta ai dati è dist1." << endl; 	
	}

	myApp -> Run(); 
	
	return 0;
}
