#include <cmath>	
#include <cstdlib>
#include <iostream>
#include "data.h"

int main () {

	int a, b, c;
	
	data A(a, b, c);
	
	A.Set(a, b, c);
	
	/*if (A.Bisestile() == true) {
		
		std::cout << "L'anno è bisestile." << std::endl;
	
	} else {
	
	std::cout << "L'anno non è bisestile." << std::endl;
	
		}  
		
	if (A.Valida() == true) {
		
		std::cout << "La data è valida." << std::endl;
	
	} else {
	
	std::cout << "La data non è valida." << std::endl;
	
	}*/
	
	A.Print();
	
	return 0;
}
