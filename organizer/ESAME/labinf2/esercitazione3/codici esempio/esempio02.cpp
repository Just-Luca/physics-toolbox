 #include <cstdlib>
 #include <ctime>
 #include <iostream>
 #include <cmath>

 double rand_range(double min, double max) {
 	return min + (max - min) *
	       rand() / (1. * RAND_MAX);
 }

 double rand_CLT(double xMin, double xMax,
                 int tries) {
 	double x = 0.;

	for (int i = 0; i < tries; ++i) {
		x += rand_range(xMin, xMax);
	}

	return x / tries;
 }

 int main() {
	srand(time(NULL));
	int max_num = 100000;

	for (int i = 0; i < max_num; ++i) {
		double numero_casuale =
		       rand_CLT(-1, 1, 10);

		std::cout << "Numero casuale: "
		          << numero_casuale << std::endl;
	}

	return 0;
 }



