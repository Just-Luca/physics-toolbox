//Questo programma chiede all'utente di inserire un intero a scelta tra 1 e 2, restituisce a terminale l'intero inserito o segnala un errore in caso di inserimento di altri interi

#include <iostream>

int main ()
{	
	int intero;
	
	std::cout << "Inserisci un intero a scelta tra 1 e 2: ";
	std::cin >> intero;
	
	if (intero == 1 || intero == 2)
		std::cout << "Hai inserito l'intero " << intero <<std::endl;

	else
		std::cout << "L'intero inserito non è compreso tra 1 e 2" << std::endl;
}
