#include <iostream>
#include <cmath>

bool Solve2ndDegree(double *k, double *s) { /* double *k e double *s indicano rispettivamente il 							vettore dei coefficienti e delle soluzioni*/
	double DELTA = (pow((-k[1]),2)-4*k[0]*k[2]);
	
	if (DELTA < 0) {	
	
		return false;
	}
	else if (DELTA > 0) {
	
		s[0] = ((-k[1]-sqrt(DELTA))/2*k[0]);
		s[1] = ((-k[1]+sqrt(DELTA))/2*k[0]);
	
		return true;
	}
	else {
		s[0] = (-k[1]/2*k[0]);
		
		return true;
	}
}

int main () {
	
	double coefficienti[3];
	double radici[2];
	
	std::cin >> coefficienti[0];
	std::cout << "coefficiente di secondo grado: "
		  << coefficienti[0] << std::endl;
	
	std::cin >> coefficienti[1];
	std::cout << "coefficiente di primo grado: "
		  << coefficienti[1] << std::endl;
	
	std::cin >> coefficienti[2];
	std::cout << "termine noto: " 
		  << coefficienti[2] << std::endl;
	
	
	if (Solve2ndDegree(coefficienti, radici) == true) {
		
		std::cout << "L'equazione vale: "
			  << radici[0] << " e " << radici[1] 
			  << std::endl;
	}
	else {
		std::cout << "L'equazione non ha soluzioni reali."
			  << std::endl;
	}
	
	return 0;
}
