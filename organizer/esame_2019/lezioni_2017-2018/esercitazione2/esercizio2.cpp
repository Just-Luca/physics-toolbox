//Questo programma dichiara un puntatore e cerca di assegnargli direttamente un valore numerico.

#include <iostream>

int main ()
{
	int* ptr;
	*ptr = 25;

	std::cout << "Il puntatore è assegnato al valore numerico " << *ptr << std::endl;
	return 0;
}
