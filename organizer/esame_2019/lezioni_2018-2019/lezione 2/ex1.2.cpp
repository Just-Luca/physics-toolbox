#include <iostream>

int main() {

	int a = 5;
	
	std::cout << "Il valore della prima variabile è: " << a << std::endl;
	std::cout << "L'indirizzo della prima variabile è: " << &a << std::endl;
	
	int* b = &a;
	
	std::cout << "Il valore della prima variabile dopo l'assegnazione è: " << a << std::endl;
	std::cout << "L'indirizzo della prima variabile dopo l'assegnazione è: " << &a << std::endl;
	std::cout << "Il valore della seconda variabile è: " << *b << std::endl;
	std::cout << "L'indirizzo della seconda variabile è: " << &b << std::endl;
	
	return 0;
}
