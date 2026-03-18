// c++ -o ErroreMedia ErroreMedia.cpp myLib.cc `root-config --glibs --cflags`

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
	int M=10000;
	double a=0., b=10.;	
	
	TH1F h1 ("name", "title", 100, 4.7, 5.3);
	double mean, random;
	for (int i=0; i<N; i++) {
		mean=0;
		for (int j=0; j<M; j++) {
			random = rand_range(a,b);
			mean += random;
		}
		mean /= M;
		h1.Fill(mean);
	}
	
	TCanvas c1;
	h1.Draw();
	c1.Print("isto.png","png");

	return 0;
 }
 
 
