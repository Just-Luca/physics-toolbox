//Questo programma assegna il valore di una variabile ad un'altra usando un puntatore. Inoltre stampa a terminale il valore e l'indirizzo di ogni variabile prima e dopo l'assegnazione.

#include <iostream>

int main ()
{
	double PrimoValore, SecondoValore;
	double* ptr;

	std::cout << "Inserisci il primo valore: ";
	std::cin >> PrimoValore;
	std::cout << "Inserisci il secondo valore: ";
	std::cin >> SecondoValore;

	std::cout << "Il primo valore vale " << PrimoValore << " e il suo indirizzo è " << &PrimoValore << std::endl;
	std::cout << "Il secondo valore vale " << SecondoValore << " e il suo indirizzo è " << &SecondoValore << std::endl;

	ptr = &PrimoValore;
	*ptr = SecondoValore;

	std::cout << "Il primo valore ora vale " << *ptr << " e il suo indirizzo è " << &PrimoValore << std::endl;
	std::cout << "Il secondo valore ora vale " << SecondoValore << " e il suo indirizzo è " << &SecondoValore << std::endl;

	return 0;
}
