// c++ -o esercizio2 esercizio2.cpp myLib.cc `root-config --glibs --cflags`

 #include <cstdlib>
 #include <ctime>
 #include <iostream>
 #include <cmath>
 #include <TH1F.h>
 #include <TCanvas.h>
 
 #include "myLib.h"
 
 int main() {
 	srand(time(NULL));
	int N=1000;
	int M;
	double mu, sigma;
	
	std::cout<< "Digitare quanti numeri campionare da una pdf gaussiana: ";
	std::cin>>M;
	std::cout<< "Impostare MU e SIGMA della pdf gaussiana: ";
	std::cin>>mu>>sigma;	
	
	TH1F h1 ("name", "title", 100, mu-5*sigma/sqrt((double)M), mu+5*sigma/sqrt((double)M));
	double mean, random, MeanMu=0., SigmaMu=0.;
	for (int i=0; i<N; i++) {
		mean=0;
		for (int j=0; j<M; j++) {
			random = rand_TAC_gaus(mu, sigma);
			mean += random;
		}
		mean /= M;
		h1.Fill(mean);
		MeanMu += mean;
		SigmaMu += mean*mean;
	}
	
	MeanMu /= (double)N;
	SigmaMu = sqrt(SigmaMu/(double)N - MeanMu*MeanMu);
	
	std::cout<< "Per il TLC, la deviazione std della media di "<<M<<" numeri estratti da una pdf gaussiana con sigma = "
			<<sigma<<" è:\n" <<sigma/sqrt((double)M) <<std::endl;
	std::cout<< "Il valore stimato per la dev std della media campionando la pdf della media è:\n"<<SigmaMu<<std::endl;
	
	std::cout<<"Il rapporto tra dev std della pdf gaussiana di partenza e dev std della media è:\n"<<sigma/SigmaMu<<std::endl;
		
	
	TCanvas c1;
	h1.Draw();
	c1.Print("isto.png","png");

	return 0;
 }
 
 
