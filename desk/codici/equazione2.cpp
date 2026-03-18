#include <iostream>
#include <cmath>

bool Solve2ndDegree(double *k, double *s) { /* double *k e double *s indicano rispettivamente il 							vettore dei coefficienti e delle soluzioni*/
	double DELTA = (pow((-k[1]),2)-4*k[0]*k[2]);
	
	if (k[0] != 0 && k[1] != 0 && k[2] == 0) {
	
		s[0] = 0;
		s[1] = (-k[1]/k[0]);
		
		return true;
	}
	
	else if (k[1] != 0 && k[0] == 0) {
		
		s[0] = (-k[2]/k[1]);
		s[1] = s[0];
		
		std::cout << "NB: è di primo grado, quindi esiste un'unica soluzione. ";	
		return true; 
	}
	
	else if (DELTA < 0) {
	
		return false;
	}
		
	else if (DELTA > 0) {
		
		s[0] = ((-k[1]-sqrt(DELTA))/2*k[0]);
		s[1] = ((-k[1]+sqrt(DELTA))/2*k[0]);
		
		return true;
	}
		
	else {
		s[0] = (-k[1]/2*k[0]);
		s[1] = s[0];
		
		return true;
	}
}

int main () {
	
	double coefficienti[3];
	double radici[2];
	
	
	std::cout << "Coefficiente di secondo grado: ";
	std::cin >> coefficienti[0];
	
	std::cout << "Coefficiente di primo grado: ";
	std::cin >> coefficienti[1];
	
	std::cout << "Termine noto: "; 
	std::cin >> coefficienti[2];
	
	if (coefficienti[0] == 0 && coefficienti[1] == 0) {
		
		std::cout << "Non ha senso." << std::endl;	
	}
	
	else if (Solve2ndDegree(coefficienti, radici) == true) {
		
		std::cout << "L'equazione ("<< coefficienti[0]
			  << ")x² + (" << coefficienti[1]
			  << ")x + (" << coefficienti[2]
			  << ") = 0 vale: "
			  << radici[0] << " e " << radici[1] 
			  << std::endl;
	}
			
	
	
	else {
		std::cout << "L'equazione non ha soluzioni reali."
			  << std::endl;
	}
	
	return 0;
}
