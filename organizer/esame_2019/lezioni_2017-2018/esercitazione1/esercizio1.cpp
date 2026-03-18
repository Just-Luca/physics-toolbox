//Questo programma legge due interi e ne restituisce il rapporto

#include <iostream>

int main ()
{
	int PrimoNumero, SecondoNumero;
	float Rapporto;

	std::cout << "Primo Intero: ";		//inserisco il primo intero
	std::cin >> PrimoNumero;
	std::cout <<"Secondo Intero: ";		//inserisco il secondo intero
	std::cin >> SecondoNumero;

	Rapporto = static_cast<float>(PrimoNumero) / SecondoNumero;					//converto un intero in float perchè il risultato sia decimale
	std::cout <<"Il rapporto dei due interi è: " << Rapporto << std::endl;		//stampo il risultato
}
