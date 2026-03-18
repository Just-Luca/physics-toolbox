//Questo programma utilizza una funzione per ordinare gli elementi di un array di n interi

#include <iostream>
#include "myLib.h"

int main()
{
	int dim;
	std::cout << "Inserire la dimensione del vettore: ";
	std::cin >> dim;
	int vettore[dim];
	
	riempimentoRandom(vettore, dim);
	std::cout << "Il vettore è:" << std::endl;
	stampaVettore(vettore, dim);
	ordinaVettore(vettore, dim);
	
	std::cout << "Il vettore ordinato è:" << std::endl;
	stampaVettore(vettore, dim);
	
	return 0;
}

