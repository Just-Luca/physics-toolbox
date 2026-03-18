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
#include <TFitResult.h>
#include <TGraphErrors.h>
#include <TAxis.h>

#define tries 1000

int main () {

	TApplication *myApp = new TApplication("app", 0, 0);
	gStyle -> SetOptFit(1112);
	
	TCanvas *c1 = new TCanvas ("c1", "My Canvas");
	c1->Divide(2,2);
	
	int N_toy = 10;
	 
 	for (int i = 1; i < 5; i++) {
 	
 		N_toy = 10*N_toy;
 		
 		double min = -3*pow(10,3)/N_toy;
 		double max = 3*pow(10,3)/N_toy;
 		
 		double e_hat = 0.;
 		double res = 0.;
 		double sum_res = 0.;
 		double mean_res = 0.;
 		double var_res = 0.;
 		
 		TH1D *h = new TH1D ("h","distribuzione dei residui", 100, min, max);
 		
 		for (int r = 0; r < tries; r++) {
 		
 			e_hat = myEulero(N_toy);
 			res = e_hat - M_E;
 			
 			h->Fill(res);
 			
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
		h->Draw();
	
		h->SetFillColor(kYellow);
		h->GetXaxis() -> SetTitle("residui");
		h->GetYaxis() -> SetTitle("conteggi");
	
		h->Fit("gaus");
		
		double sigma = h->GetRMS();
		double sigma_err = h->GetRMSError();
		
 	}
 	
 	c1->Modified();
	c1->Update();
 	
 	myApp -> Run();
 	
	return 0;
}

