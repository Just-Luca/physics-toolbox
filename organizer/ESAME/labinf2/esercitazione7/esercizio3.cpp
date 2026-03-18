#include <string>
#include <iostream>

int main()
{
	std::string nome;
	
	std::cout << "Inserisci il tuo nome: " << std::endl;
	std::cin >> nome;
	
	std::string saluto = "Ciao, ";
	saluto += nome + "!";
	std::cout << saluto << std::endl;
	
	return 0;
}
