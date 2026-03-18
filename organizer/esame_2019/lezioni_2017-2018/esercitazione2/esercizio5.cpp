//Questo programma calcola media e varianza di 10 numeri salvati in un array con un'unica funzione che utilizzi puntatori o referenze.

#include <iostream>
#include "myLib.h"

#define N 10

int main()
{
	double Media, Varianza;
	double numeri[N];
	std::cout << "Inserisci 10 numeri reali: " << std::endl;
	
	riempiVettore(numeri, N);
	MediaVarianza(numeri, N, Media, Varianza);
	
	std::cout << "La media dei numeri è: " << Media << std::endl;
	std::cout << "La varianza dei numeri è: " << Varianza << std::endl;
	return 0;
}

