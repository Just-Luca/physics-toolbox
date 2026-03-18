/*
c++ -o esame esame.cpp `root-config --cflags --glibs`
*/

#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
//#include <cstdlib>
#include <TApplication.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <TF1.h>
#include <TStyle.h>

#define nStep 100
#define N 10000
#define rho 1
#define min 0
#define max 360

//funzione che genera un numero casuale

double rand_range (double xMin, double xMax) {
	
	return xMin + (xMax - xMin) * rand() / (1. * RAND_MAX);
}

//funzioni di fit

double myGaus (double* x, double* par) {

	return par[0] * exp(-0.5*((x[0]-par[1])*(x[0]-par[1])/(par[2]*par[2])));
}

double myPsf (double* x, double* par) {

	return x[0]*(par[0] * exp(-0.5*((x[0]-par[1])*(x[0]-par[1])/(par[2]*par[2]))));
}

int main () {
	
	int seed;
	float xi, yi, xf, yf, d, rand;
	
	xi = 0;
	yi = 0;	
	
	std::cout << "Inserire seed: ";
	std::cin >> seed;
	
	srand(seed);
	
	rand = 0;
	
	xf = xi;
	yf = yi;
	
	
	// con questo ciclo for mi calcolo la posizione finale (xf,yf) dopo nStep
	
	for (int i = 0; i < nStep; i++) {
		
		rand = rand_range (min, max);
		
		xf += xi + rho*cos(rand);
		yf += yi + rho*sin(rand);
	}
	
	d = sqrt(xf*xf + yf*yf);
	
	std::cout << "La distanza d a cui il soggetto è arrivato rispetto al punto di partenza è: \n d = " << d << std::endl;
	
	TApplication *myApp = new TApplication("app", 0, 0);
	
	TH1F *pdf = new TH1F ("istogramma", "Istogramma", 30, -1, 26);
	
	
	// tramite il ciclo for riempio l'istogramma
	
	for (int t = 0; t < N; t++) {
	
		d = 0;
		xf = 0;
		yf = 0;
	
		for (int j = 0; j < nStep; j++) {
	
		 	rand = rand_range (min, max);
			xf += xi + rho*cos(rand);
			yf += yi + rho*sin(rand);
		 }
		
		d = sqrt(xf*xf + yf*yf);
		pdf->Fill(d);
	}
	
	TCanvas *c1 = new TCanvas ();
	
	pdf->Draw();
	
	pdf->SetFillColor(kGreen);
	pdf->Draw("E same");
	
	int nPar = 3;
	
	double mu = pdf->GetMean();
	double si = pdf->GetStdDev();
	
	TF1 *f1 = new TF1 ("Gaus", myGaus, -10, 10, nPar);
	f1->SetParameter(0, 1.); 
	f1->SetParameter(1, mu);
	f1->SetParameter(2, si);
	
	// fitto l'istogramma con le due funzioni
	
	TF1 *f2 = new TF1 ("Psf", myPsf, -10, 10, nPar);	
	f2->SetParameter(0, 1.);
	f2->SetParameter(1, mu);
	f2->SetParameter(2, si);
	
	f2->SetLineColor(kBlue);
	
	pdf->Fit("Psf","+");
	pdf->Fit("Gaus","+");
	
	// Per mancanza di tempo ho stampato a terminale i risultati dell'ultimissimo punto della consegna anzichè creare un file tramite la classe ofstream
	
	double A = f1->GetChisquare()/f1->GetNDF();
	double B = f2->GetChisquare()/f2->GetNDF();
	
	std::cout << "Il chi-quadro ridotto associato alla gaussiana è: " << A << std::endl;
	std::cout << "Il chi-quadro ridotto associato alla point spread function è: " << B << std::endl;
	
	if (abs(1-B) < abs(1-A)) {

		std::cout << "ROOT: la funzione che meglio si adatta ai dati è la point spread function." << std::endl;
	} 

	else { std::cout << "ROOT: la funzione che meglio si adatta ai dati è la gaussiana." << std::endl; 	
	}

	c1->Modified();
	c1->Update();
	
	myApp -> Run(); 

	return 0;	
}













