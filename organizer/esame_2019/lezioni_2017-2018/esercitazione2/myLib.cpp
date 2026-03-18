#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <cmath>

#include "myLib.h"

void MediaVarianza(double* numeri, int N, double& Media, double& Varianza)
{
	double somma = 0, sommaquadrati, scarto;
	for (int j = 0; j < N; j++)
		somma += numeri[j];
	
	Media = somma/N;
	
	for (int j = 0; j < N; j++)
	{
		scarto = (Media - numeri[j]);
		sommaquadrati += pow (scarto, 2);
	} 
	Varianza = sommaquadrati/N;
}


void ordinaVettore(int* vettore, int dim)
{
	int posmin, aux;
	int minimo;
	
	for(int i=0; i<dim; i++)
	{
		minimo = vettore[i];
		posmin = i;
		for(int j=i+1; j<dim; j++)
		{
			if(vettore[j] < minimo)
			{
				minimo = vettore[j];
				posmin = j;
			}
		}
		aux = vettore[i];
		vettore[i] = minimo;
		vettore[posmin] = aux;
	}
}


void riempimentoRandom(int* vettore, int dim)
{
	srand(time(NULL));
	for (int i=0; i<dim; i++)	
		vettore[i] = rand()%100;
}


void riempiVettore(double* numeri, int N)
{
	for (int i = 0; i < N; i++)
		std::cin >> numeri[i];
}


void stampaVettore(int* vettore, int dim)
{
	for(int i=0; i<dim; i++)
		std::cout << vettore[i] << std::endl;
}


