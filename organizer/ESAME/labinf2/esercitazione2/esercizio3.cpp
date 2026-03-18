//Questo programma utilizza le istruzioni new e delete per creare e distruggere una variabile double ed un array di double.

#include <iostream>

double* CreaVettore(int dim)
{
	double* array = new double[dim];
	return array;
}

int main ()
{	
	int dim;
	std::cout << "Inserisci la dimensione del vettore: ";
	std::cin >> dim;
	
	double* vettore = CreaVettore(dim);
	std::cout << "Inserisci le entrate del vettore: ";
	for (int i = 0; i < dim; i++)
	{
		std::cin >> vettore[i];
		std::cout << "L'entrata " << i+1 << "-esima del vettore è: " << vettore[i] << std::endl;
	}

	delete vettore;

	double* numero;
	numero = new double(3.1415);
	std::cout << "Il valore di pi greco è: " << *numero << std::endl;
	delete numero; 
}
