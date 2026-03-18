//Questo programma memorizza dieci numeri in un array, quindi ne calcola media e varianza

#include <iostream>
#include <cmath> 

#define N 10


float media (float numeri[])
{
	float somma = 0, MEDIA;
	for (int j = 0; j < N; j++)
		somma += numeri[j];
		 
	MEDIA = somma/N;
	return MEDIA;
}

float varianza (float numeri[], float media)
{
	float sommaquadrati, scarto, VARIANZA;
	for (int j = 0; j < N; j++)
	{
		scarto = (media - numeri[j]);
		sommaquadrati += pow (scarto, 2);
	} 
	VARIANZA = sommaquadrati/N;
	return VARIANZA;
}	

int main ()
{
	float MEDIA, VARIANZA;
	float numeri[N];
	std::cout << "inserisci 10 numeri: ";
	
	for (int i = 0; i < N; i++)
		std::cin >> numeri[i];
	
	MEDIA = media(numeri);
	VARIANZA = varianza(numeri, MEDIA);
	
	std::cout << "La media dei numeri e': " << MEDIA << std::endl;
	std::cout << "La varianza dei numeri e': "<< VARIANZA << std::endl;

	return 0;
}
	
