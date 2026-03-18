#include <cmath>	
#include <cstdlib>
#include "istogramma.h"
#include "myLib.h"
#include <iomanip> // stampa a terminale

istogramma::istogramma(int nBIn, float min, float max) {
	nBin_p = nBin;
	min_p = min;
	max_p = max;
	step_p = (max_p - min_p)/nBin_p;
	binContent_p = new int [nBin_p];
	
	for (int i = 0; i < nBin_p; i++) {
		binContent_p[i] = 0;
	}
	
	
}
