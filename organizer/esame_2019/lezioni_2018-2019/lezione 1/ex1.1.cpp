#include <iostream>
#include <cmath>

int main() {
	
	int a, b;
	
	std::cout << "Inserisci due numeri interi:" << std::endl;
	std::cin >> a >> b ;
	
	float c;
	c = (float(a))/b ;
	
	std::cout << "Il rapporto dei due numeri inseriti è: " << c << std::endl;
	
	return 0;
} 
