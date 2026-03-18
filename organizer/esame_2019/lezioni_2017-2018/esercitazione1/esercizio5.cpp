//Questo programma calcola il fattoriale di un intero non negativo

#include <iostream>

int fattoriale(int input)
{
	if (input < 0)
	{
		std::cout << "L'intero inserito è negativo" << std::endl;
		return -1;
	}
	else if (input == 0)
	{
		std::cout << "Il fattoriale di 0 è 1" << std::endl;
		return 1;
	}
	else
	{
		int risultato = 1;
		for (int i = input; i > 0; i--)
			risultato = risultato * i;

		std::cout << "Il fattoriale dell'intero inserito è " << risultato << std::endl;
		return risultato;
	}
}

int main()
{
	int intero;
	std::cout << "Inserisci un intero non negativo: ";
	std::cin >> intero;
	
	fattoriale(intero);
}
