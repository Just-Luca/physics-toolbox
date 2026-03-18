#include <iostream>

double* creavettore(int dim)
{
	double* array = new double[dim];
	return array;
}


int main()
{
	int dim = 4;
	double* vettore = creavettore(dim);
	
	for(int i=0; i<dim; i++)
		std::cin >> vettore[i];
	
	delete vettore;
	
	std::cout << "Fine vettore" << std::endl;
	
	double* numero = new double;
	std::cout << *numero << std::endl;
	std::cout << "Riempi numero" << std::endl;
	
	std::cin >> *numero;
	std::cout << *numero << std::endl;
	
	delete numero;

	return 0;
}
