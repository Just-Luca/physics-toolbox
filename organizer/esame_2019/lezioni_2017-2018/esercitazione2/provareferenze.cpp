#include <iostream>

void modificabycopia(int numero, int input)
{
	numero = input;
	std::cout << "numero: " << numero << std::endl;
	return;
}

void modificabyref(int& numero, int input)
{
	numero = input;
	return;
}


int main()
{
	int prova = 4;
	int input = 5;
	
	modificabycopia(prova, input);
	std::cout << "prova: " << prova << std::endl;
	input = 6;
	modificabyref(prova, input);
	std::cout << "prova: " << prova << std::endl;
	
	return 0;
}
