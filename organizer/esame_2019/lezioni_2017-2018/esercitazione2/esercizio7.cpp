//Questo programma crea un vettore tramite una funzione void

#include <iostream>
#include "myLib.h"

void creaVettore((double*)* ptr, int dim)
{
	*ptr = new double[dim];	
}

int main()
{
	int dim;
	double* ptr = NULL;
	std::cin >> dim;
	
	creaVettore(&ptr, dim);
	riempimentoRandom(ptr, dim);
	stampaVettore(ptr, dim);
	
	return 0;
}

