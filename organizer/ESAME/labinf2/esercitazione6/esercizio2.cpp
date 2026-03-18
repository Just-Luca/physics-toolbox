#include "data.h"
#include <iostream>
#include <cstdlib>

int main()
{
	data data1 (13, 03, 2018);
	data1.stampa();
	if (data1.valida()) std::cout << "VALIDA" << std::endl;
	else std::cout << "NON VALIDA" << std::endl;

	data data2 (34, 01, 2013);
	data2.stampa();
	if (data2.valida())
		std::cout << "VALIDA" << std::endl;
	else std::cout << "NON VALIDA" << std::endl<<std::endl;
	
	data data3 (14,03,2018);
	data data4 (11,03,1993);
	data3.stampa();
	data4.stampa();

	if (data3 < data4)
		std::cout << "data3 < data4" << std::endl;
	
	if (data3 == data4)
		std::cout << "data3 == data4" << std::endl;
	
	if (data3 > data4)
		std::cout << "data3 > data4" << std::endl;
	
	std::cout << "Il numero di giorni trascorso tra data3 e data4 è " << data3.diff_giorni(data4) << std::endl << std::endl;

	std::cout << "Oggi è " << data1.giorno_settimana() << " ";
	data1.stampa();
	
	std::cout << "Il giorno 14/03/2018 è un " << data3.giorno_settimana() << std::endl;
	
	std::cout << "Il giorno 11/03/1993 è un " << data4.giorno_settimana() << std::endl;
	
	data Natale2018 (25,12,2018);
	std::cout << "L'anno prossimo Natale sarà di " << Natale2018.giorno_settimana() << std::endl;

}

