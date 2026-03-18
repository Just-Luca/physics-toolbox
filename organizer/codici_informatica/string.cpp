#include <string>
#include <iostream>

int main () {

	std::string NOME;
	
	std::cout << "Inserisci il tuo nome: ";
	std::cin >> NOME;
	
	std::cout << "Ciao " << NOME << "!" << std::endl;
	
	return 0;
}
