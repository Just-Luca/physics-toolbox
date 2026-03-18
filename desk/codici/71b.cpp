#include <iostream>
#include "Array.h"
#define inserisci 'i'
#define togli 't'
#define esci 'e'

int main() {
	
	int elementi;
	int a, b;
	char c;

	//array semplice di int
	SimpleArray<int> array(elementi);
	
	std::cout << "Inserisci la grandezza del vettore: ";
	std::cin >> elementi;
	
	std::cout << "ISTRUZIONI" << std::endl;
	std::cout << "Premi: " << std::endl;
	std::cout << "	  -'i' per inserire un elemento;" << std::endl;
	std::cout << "	  -'t' per togliere un elemento;" << std::endl;
	std::cout << "	  -'e' per terminare di riempire il vettore." << std::endl;
	
	std::cin >> c;
	
	while (c =! esci) {
	
		for(int i = 0; i < elementi; ++i) {
		
			if (c == inserisci) {
				std::cout << "Inserisci un nuovo elemento: ";
				std::cin >> a;	
 				array.push(a);
			} 
		
			else if (c == togli) {
				std::cout << "Quale elemento vuoi eliminare?" << std::endl;
				std::cin >> b;
				array.pop(b);
			}
		}
	}
	
	array.rilettura();
	
	std::cout << "Il numero degli elementi del vettore è: " 
		    << array.size() << std::endl;

	return 0; 
}


