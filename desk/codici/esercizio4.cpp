 // c++ -o esercizio4 esercizio4.cpp myLib.cc `root-config --glibs --cflags`
 
 #include <cstdlib>
 #include <ctime>
 #include <iostream>
 #include <cmath>
 
 #include <TH1F.h>
 #include <TCanvas.h>
 
 #include "myLib.h"
 
 int main ()  {

	srand(time(NULL));
	
	int N = 2;
	
	std::cout<<"Quanti numeri casuali vuoi estrarre e mediare? ";
	std::cin>>N;
	
	int M = 10000;
	float xMin=0.;
	float xMax=1.;
	float mu=0.25;
	
	TH1F h1 ("h1","rand_TCL",100, xMin, xMax);
	
	double random, sum=0., sumSq=0.;
	for (int i=0; i<M; i++) {
		random=0.;
		for (int j=0; j<N; j++) {
			random += rand_FCI_Exp(mu);
		}
		random /= (double)N;
		
		sum += random;
		sumSq += random*random;
		h1.Fill(random);
	}
	double mean = sum/(double)M;
	double var = sumSq/(double)M - mean*mean;
	
	std::cout << "Media: "<<mean << std::endl;	
	std::cout << "Varianza: "<<var << std::endl;

	TCanvas c1;	
	h1.Draw();
	c1.Print("rand_TCL.png", "png");
	
	return 0;
}
