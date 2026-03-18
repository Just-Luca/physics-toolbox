#include <iostream>

int main() {
	int numero;

	std::cout << "Inserisci un numero: " << std::endl;
	std::cin >> numero;

	if (numero > 10 || numero < -10) {
		std::cout << "Hai inserito " << numero
		          << " che e`un numero con due o "
		          << "piu` cifre." << std::endl;
	}
	else {
		std::cout << "Hai inserito " << numero
		          << " che e` un numero con una "
		          << "sola cifra." << std::endl;
	}

	return 0;
}
