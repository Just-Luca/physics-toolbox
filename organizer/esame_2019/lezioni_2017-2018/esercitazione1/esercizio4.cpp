//Questo programma indica se l'intero inserito dall'utente sia pari o dispari

#include <iostream>

void paridispari(int intero)
{
	if (intero % 2 == 0)
		std::cout << "L'intero è pari" << std::endl;	
	else
		std::cout << "L'intero è dispari" << std::endl;

	return;
}

int main ()
{
	int intero;
	std::cout << "Inserisci un intero: ";
	std::cin >> intero;
	
	paridispari(intero);
}


