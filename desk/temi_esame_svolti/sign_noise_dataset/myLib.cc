#include <cstdlib>
#include <iostream>
#include <cmath>
#include <TCanvas.h>
#include <TH1F.h>
#include <fstream>
#include <TStyle.h>
#include <TApplication.h>
#include <TH1D.h>
#include <TF1.h>
#include "myLib.h"

double rand_range (double xMin, double xMax) {
	
	return xMin + (xMax - xMin) * rand() / (1. * RAND_MAX);
}

double rand_media (double xMin, double xMax, int tries) {
	
	double x = 0.;
	
	for (int i = 0; i < tries; ++i) {
	
		x += rand_range (xMin, xMax);
	}
	
	return x/tries;
}
	
double rand_varianza (double xMin, double xMax, int tries) {

	double sum = 0;
	double sumSq = 0;
	
	for (int i = 0; i < tries; ++i) {
		
		double rand = rand_range (xMin, xMax);
		sum += rand;
		sumSq += rand*rand;
	}
	
	return sumSq/tries - (sum/tries)*(sum/tries);
}

double rand_dvz_std (double xMin, double xMax, int tries) {
	
	return sqrt (rand_varianza (xMin, xMax, tries));
}

void isto_bin100_G (double xMin, double xMax, int tries) {
	
	TH1F pdf ("istogramma", "Istogramma-Gaus", 100, xMin, xMax);
	
		int N = 10;
	
		for (int i = 0; i < tries; i++) {
	
			double media = rand_media (xMin, xMax, N);
			pdf.Fill(media);
		}
	
		TCanvas cnv;
		pdf.Draw();
		pdf.Fit("gaus");
		cnv.Print("istogramma.png", "png");
}

double f_Cauchy (double x) {

	return (1/M_PI)*(1/(1+pow(x, 2)));
}

double f_Gaus (double x) {

	return exp(-4*x*x);
}

double rand_TAC_G (double xMin, double xMax, double yMin, double yMax) {

	double x = 0.;
	double y = 0.;
	
	do {
		x = rand_range (xMin, xMax);
		y = rand_range (yMin, yMax);
	} 
	
	while (y > f_Gaus(x));
	
	return x;
}

double fGaus (double x, double mu, double sigma) {

 	return exp(-0.5*pow((x-mu),2)/(sigma*sigma))/sqrt(2*M_PI*sigma*sigma);
}
 
double rand_TAC_Gaus (double mu, double sigma) {

	double xMin = mu - 5*sigma;
	double xMax = mu + 5*sigma;
	double yMin = 0.;
	double yMax = 1./sqrt(2*M_PI*sigma*sigma);
	double x = 0., y = 0.;
	
	do {
		x = rand_range(xMin, xMax);
		y = rand_range(yMin, yMax);
		
	} 
	
	while (y > fGaus(x, mu, sigma));
	
	return x;
}

double rand_TAC_C (double xMin, double xMax, double yMin, double yMax) {

	double x = 0.;
	double y = 0.;
	
	do {
		x = rand_range (xMin, xMax);
		y = rand_range (yMin, yMax);
	} 
	
	while (y > f_Cauchy(x));
	
	return x;
}

void isto_bin100_C (double xMin, double xMax, double yMin, double yMax, int tries) {
	
	TH1F pdf ("istogramma", "Istogramma-Gaus", 100, xMin, xMax);
	
		double rand = 0.;
	
		for (int i = 0; i < tries; ++i) {
	
			double rand = rand_TAC_C (xMin, xMax, yMin, yMax);
			pdf.Fill(rand);
		
		}
	
		TCanvas cnv;
		pdf.Draw();
		pdf.Fit("gaus");
		cnv.Print("istogramma.png", "png");
}

double f_Exp (double y , double u) {
	
	return -u*log(1-y);
}

double rand_FCI_Exp (double xMin, double xMax, double u) {

	double x,y;
	
	y = rand_range (xMin, xMax);
	x = f_Exp(y,u);
	
	return x;
}

void isto_bin100_Exp (double xMin, double xMax, double u, int tries) {
	
	TH1F exp ("istogramma", "Istogramma-Exp", 100, xMin, xMax);
	
		double rand;
	
		for (int i = 0; i < tries; ++i) {
	
			rand = rand_FCI_Exp (xMin, xMax, u);
			exp.Fill(rand);
		
		}
	
		TCanvas cnv;
		exp.Draw();
		exp.Fit("gaus");
		cnv.Print("istogramma.png", "png");
}

bool HitMiss_Gaus(double xMin, double xMax, double yMin, double yMax, double mu, double sigma) {
 	
	double x = 0., y = 0.;
	x = rand_range(xMin, xMax);
	y = rand_range(yMin, yMax);
	if (y < fGaus(x, mu, sigma)) return true;
	else return false;
}

double Area (double a, double b, double c,double d) {
	// a < b e c < d
	return (b-a)*(d-c);
}

double Integral_HM (int nHit, int N, double Area) {

	return nHit*Area / (double)N;
}

double p_HM (int nHit, int N) {

	return nHit / (double)N;
}

double Var_HM (double Area, double p, int N) {

	return Area*Area / (double)N*p*(1. - p);
}

double StdVar_HM (double Var) {

	return sqrt(Var);
}

double myGauss (double* x, double* par) {

	return par[0] * exp(-0.5*((x[0]-par[1])*(x[0]-par[1])/(par[2]*par[2])));
}

double myParabola (double* x, double* par) {

	return par[0] + par[1]*x[0] + par[2]*x[0]*x[0];
}

double myExp (double* x, double* par) {
	
	return par[0]*exp(-x[0]/par[1]);
}

double sum (double* x, double* par) {

	double val = myGauss(x, par) + myParabola(x, &par[3]);
	
	return val;
}

bool ReadData(char* fileName, TH1D* myHisto) {

	double val;
	std::fstream f;
	f.open(fileName,std::ios::in);

	if (f.good() == false) return false;
  
	while (true) {
	
		f >> val;
		
		if (f.eof() == true) break;
		
		myHisto->Fill(val);
	}
	
	return true;
}

void ComputeChi2(TH1D* myHisto, TF1* myFun, double& chi2, double& NDF) {

	double result = 0;
	
	for (unsigned int i = 1; i <= myHisto->GetNbinsX(); i++) {
	
      	result += pow((myHisto->GetBinContent(i) - myFun->Eval(myHisto->GetBinCenter(i))),2.) / myHisto->GetBinContent(i);
	}

	chi2 = result;
	NDF  = myHisto->GetNbinsX() - myFun->GetNpar();
}




 






 

