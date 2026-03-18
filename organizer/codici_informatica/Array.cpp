#include <iostream>
#include "Array.h"

int main() {
	
	int elementi = 10;
	int a, b;

	//array semplice di int
	SimpleArray<int> array(elementi);
	std::cout << "Array riempito con int: " << std::endl;
	
  	//riempimento
	for(int i = 0; i < elementi; ++i)
 		array.element(i) = 2*i;
			    
	array.rilettura();
			    
	std::cout << "Il numero degli elementi del vettore è: " 
		    << array.size() << std::endl;

	std::cout << "Inserisci un nuovo elemento: ";
	std::cin >> a;	
 	
 	array.push(a);
	
	array.rilettura();
	
	std::cout << "Inserisci un nuovo elemento: ";
	std::cin >> a;	
 	
 	array.push(a);
	
	array.rilettura();
	
	std::cout << "Inserisci un nuovo elemento: ";
	std::cin >> a;	
 	
 	array.push(a);
	
	array.rilettura();
	
	std::cout << "Il numero degli elementi del vettore è: " 
		    << array.size() << std::endl;

	std::cout << "Quale elemento vuoi eliminare?" << std::endl;
	std::cin >> b;
		
	array.pop(a);
	
	array.rilettura();
	
	std::cout << "Il numero degli elementi del vettore è: " 
		    << array.size() << std::endl;

	return 0; 
}


