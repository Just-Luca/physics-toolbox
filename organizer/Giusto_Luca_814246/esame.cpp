/*
c++ -o esame esame.cpp Lib.cc `root-config --glibs --cflags`
*/

#include <iostream>
#include <cmath>
#include "Lib.h"

#include <TApplication.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TF1.h>
#include <TStyle.h>
#include <TGraphErrors.h>
#include <TAxis.h>

#define tries 1000

double myFit (double* x, double* par) {

	return par[0]/sqrt(x[0]);
}

int main () {

	TApplication *myApp = new TApplication("app", 0, 0);
	gStyle -> SetOptFit(1112);
	
	TCanvas *c1 = new TCanvas ("c1", "My Canvas1");
	c1->Divide(2,2);
	
	TCanvas *c2 = new TCanvas ("c2", "My Canvas2");
	
	int N_toy = 10;
	
	TGraphErrors* myGraph = new TGraphErrors();
	
	double sigma;
	double sigma_err;
	
	TH1D *isto[4];
	
 	for (int i = 1; i < 5; i++) {
 	
 		N_toy = 10*N_toy;
 		
 		double min = -3*pow(10,3)/N_toy;
 		double max = 3*pow(10,3)/N_toy;
 		
 		double e_hat = 0.;
 		double res = 0.;
 		double sum_res = 0.;
 		double mean_res = 0.;
 		double var_res = 0.;
 		
 		if (i == 1) {
 		
 			isto[i] = new TH1D ("h1","distribuzione dei residui, N_toy = 10^2", 100, min, max);
 		}
 		
 		else if (i == 2) {
 		
			isto[i] = new TH1D ("h2","distribuzione dei residui, N_toy = 10^3", 100, min, max);
		}
		
		else if (i == 3) {
		
			isto[i] = new TH1D ("h3","distribuzione dei residui, N_toy = 10^4", 100, min, max);
		}
		
		else if (i == 4) {
		
			isto[i] = new TH1D ("h4","distribuzione dei residui, N_toy = 10^5", 100, min, max);
		}
 		
 		for (int r = 0; r < tries; r++) {
 		
 			e_hat = myEulero(N_toy);
 			res = e_hat - M_E;
 			
 			isto[i]->Fill(res);
 			
 			sum_res += res;
 		}
 		
 		mean_res = sum_res/tries;
 		var_res = (sum_res*sum_res)/tries - (sum_res/tries)*(sum_res/tries);
 		double devstd_res = sqrt(var_res);
 		
 		std::cout << "" << std::endl;
 		std::cout << "La media dei residui é: " << mean_res << std::endl;
 		std::cout << "La varianza dei residui é: " << var_res << std::endl;
 		std::cout << "La deviazione standard dei residui é: " << devstd_res << std::endl;
 		std::cout << "" << std::endl;
 		
 		c1->cd(i);
 		
 		c1->Modified();
		c1->Update();
		
		isto[i]->Draw();
	
		isto[i]->SetFillColor(kYellow);
		isto[i]->GetXaxis() -> SetTitle("residui");
		isto[i]->GetYaxis() -> SetTitle("conteggi");
	
		isto[i]->Fit("gaus");
		
		sigma = isto[i]->GetRMS();
		sigma_err = isto[i]->GetRMSError();
 	
 		myGraph->SetPoint(myGraph->GetN(), N_toy, sigma);
		myGraph->SetPointError(myGraph->GetN()-1, 0, sigma_err);
		myGraph->SetMarkerStyle(20);
  		myGraph->SetMarkerSize(0.2);
		myGraph->GetXaxis()->SetTitle("N_toy");
  		myGraph->GetYaxis()->SetTitle("Sigma");
 	}

	TF1* myFun = new TF1("myFun", myFit, 0, 10000, 1);
	
  	myFun->SetParameter(0, 0.87);
 	myFun->SetParName(0, "a");
 		
 	c2->cd();
 	
 	c2->Modified();
	c2->Update();
	
  	myGraph->Draw("AP");
  	myGraph->Fit("myFun");
  
 	myApp -> Run();
 	
	return 0;
}

