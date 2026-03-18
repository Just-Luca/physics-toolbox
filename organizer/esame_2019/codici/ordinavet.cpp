#include <iostream>

void OrdinaVettore (double* vet, int dim) {

	double minimo, aux;
	int posmin;
	
	for (int i = 0; i < dim; i++) {
		
		minimo = vet[i];
		posmin = i;
		
		for (int j = i+1; j < dim; j++) {
		
			if (vet[j] < minimo) {
				
				minimo = vet[j];	
				posmin = j;
			}
		}
		
	aux = vet[i];
	vet[i] = minimo;
	vet[posmin] = aux;
	
	}
} 
	

int main () {

	int dimensione;
	std::cout << "Inserire dimensione vettore: ";
	std::cin >> dimensione;
	double vettore[dimensione];
	
	std::cout << "Inserire elementi vettore: " <<std::endl;
	for (int i = 0; i < dimensione; i++) {	
		std::cin >> vettore[i];
	}
	
	std::cout << "Il vettore riordinato è: ";
	
	for (int i = 0; i < dimensione; i++) {
		
		OrdinaVettore (vettore, dimensione);
		std::cout << vettore[i] << " ";
	}
	
	std::cout << std::endl;	
			
	return 0;
}
