#include <iostream>
#include <fstream>
#include <cstdlib>

#include "misura.h"


int main ()
{
	misura c("misura.txt");

	misura c1;
	misura ni;

	c.Somma(c1); //così sommo c+c1 e stampo il risultato
	
	std::cout << "\nc : velocità della luce da file misura.txt" << std::endl;
	std::cout << "c1: velocità della luce accertata" << std::endl;
	std::cout << "ni: velocità del neutrino" << std::endl;
			  
			  
	std::cout << "\nCompatibilita` tra c e c1" << std::endl;
	c.Confronta(c1);

	std::cout << "\nCompatibilita` tra c1 e ni" << std::endl;
	c1.Confronta(ni);

	std::cout << "\nCompatibilita` tra ni e c" << std::endl;
	ni.Confronta(c);
}
