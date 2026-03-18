 #include <cstdlib>
 #include <ctime>
 #include <iostream>
 #include <cmath>

 double f_gaus(double x) {
 	return exp(-4*x*x);
 }

 double rand_range(double min, double max) {
 	return min + (max - min) * rand() / (1. * RAND_MAX);
 }

 double rand_TAC(double xMin, double xMax, double yMin, double yMax) {
 	double x=0., y=0.;
	do {
		x = rand_range(xMin, xMax);
		y = rand_range(yMin, yMax);
	} while (y > f_gaus(x));
	return x;
 }

 int main() {
	srand(time(NULL));
	int max_num = 100000;
	double numero_casuale=0.;
	for (int i = 0; i < max_num; ++i) {
		numero_casuale = rand_TAC(-1., 1., 0., 1.);
		std::cout << numero_casuale << std::endl;
	}
	return 0;
 }



