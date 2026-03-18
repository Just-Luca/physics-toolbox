#include <cmath>	
#include <cstdlib>
#include "complesso.h"
#include <iostream>

int main () {
	
	double x, y;
	int z;
	double &a = x;
	double &b = y;
	int &p = z;
	
	std::cout << "Inserisci parte reale: ";
	std::cin >> x;
	
	std::cout << "Inserisci parte immaginaria: ";
	std::cin >> y;
	
//	std::cout << "Inserisci l'esponente: ";
//	std::cin >> z;
	
	complesso c(a, b);
	
	/*complesso d(4, 2);
	
	complesso e;
	
	e = c/d;*/
	
//	d = c^p;
	
	c.Print();
	
	/*complesso d(5, 2);
	
	complesso e;
	
	e = c*d;
	
	e.Print();
	
	complesso f(1, 2);
	
	complesso g;
	
	g = c*f;
	
	g.Print();*/
	
	return 0;
}

	

	
