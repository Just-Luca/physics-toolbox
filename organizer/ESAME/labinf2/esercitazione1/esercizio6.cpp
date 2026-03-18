//Questo programma calcola il fattoriale di un intero non negativo con una funzione ricorsiva

#include<iostream>

int fattoriale (int input)
{
	if(input < 0)
	{
		std::cout << "L'intero inserito e' negativo" << std::endl;
		return -1;
	}
	else if (input == 0)
		return 1;
	else
		return input * fattoriale(input-1);
}	

int main (){
	int intero;
	std::cout << "inserisci un intero non negativo: ";
	std::cin >> intero;
	
	int risultato = fattoriale(intero);
	if (risultato > 0)
		std::cout << "Il fattoriale di " << intero << " e' " << risultato << std::endl;

	return 0;
}
