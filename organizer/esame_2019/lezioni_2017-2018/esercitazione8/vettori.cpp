#include <iostream>
#include "vett2d.h"

int main()
{
	int k = 2;
	double x, y;
	std::cin >> x >> y;
	vett2d vettore1(x,y);
	
	double z, t;
	std::cin >> z >> t;
	vett2d vettore2(z,t);
		
	std::cout << "Vettore 1: ";
	vettore1.print();
	std::cout << "Vettore 2: ";
	vettore2.print();
	
	vett2d sum = vettore1 + vettore2;
	std::cout << "Somma: ";
	sum.print();
	double mod = vettore1.mod();
	std::cout << "Modulo vettore 1: " << mod << std::endl;	
	
	return 0;
}
