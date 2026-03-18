 // c++ -o esercizio3 esercizio3.cpp myLib.cc `root-config --glibs --cflags`
 
 #include <cstdlib>
 #include <ctime>
 #include <iostream>
 #include <cmath>
 
 #include <TH1F.h>
 #include <TCanvas.h>
 
 #include "myLib.h"
 
 int main ()  {

	srand(time(NULL));
	
	int N = 10000;
	float xMin=0.;
	float xMax=1.;
	float mu=0.25;
	
	TH1F h1 ("h1","rand_FCI_Exp",100, xMin, xMax);
	
	double random, sum=0., sumSq=0.;
	for (int i=0; i<N; i++) {
		random=rand_FCI_Exp(mu);
		sum += random;
		sumSq += random*random;
		h1.Fill(random);
	}
	double mean = sum/(double)N;
	double var = sumSq/(double)N - mean*mean;
	
	std::cout << "Media: "<<mean << std::endl;	
	std::cout << "Varianza: "<<var << std::endl;

	TCanvas c1;	
	h1.Draw();
	c1.Print("rand_FCI_Exp.png", "png");
	
	return 0;
}
