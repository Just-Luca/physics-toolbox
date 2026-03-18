#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

#include "myLib.h"
#define PI 3.141592

double f_Cauchy(double x)
{
	return 1/(PI*(1+pow(x, 2)));
}


double FCI(double x, double mu)
{
	return (1/mu)*(exp(-x/mu));
}


double media(double* num, int n)
{
	double avg;
	double sum = 0;
	for(int i=0; i<n; i++)
		sum += num[i];
	avg = sum/n;
	return avg;
}

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


double rand_FCI_exp(double mu)
{
	double x, y;
	y = rand_range(0, 1);
	x = -mu*log(1-y);
	return x;
}


double rand_range(double min, double max)
{
	return min + (max - min) * rand () / (1. *RAND_MAX);
}


double rand_TAC(double xMin, double xMax, double yMin, double yMax)
{
	double x=0., y=0.;
	do
	{
		x = rand_range(xMin, xMax);
		y = rand_range(yMin, yMax);
	}
	while(y > f_Cauchy(x));
	return x;
}


void riempimentoRandom(int* vettore, int dim)
{
	srand(time(NULL));
	for (int i=0; i<dim; i++)	
		vettore[i] = rand()%100;
}

void riempimentoRandom(double* vettore, int dim)
{
	srand(time(NULL));
	for (int i=0; i<dim; i++)
	{
		std::cout << i << std::endl;
		vettore[i] = rand()%100;
	}
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

void stampaVettore(double* vettore, int dim)
{
	for(int i=0; i<dim; i++)
		std::cout << vettore[i] << std::endl;
}

