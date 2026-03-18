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


double f_Gaus (double x, double mu, double sigma)
{
 	return exp(-0.5*pow((x-mu),2)/(sigma*sigma))/sqrt(2*M_PI*sigma*sigma);
}


double FCI(double x, double mu)
{
	return (1/mu)*(exp(-x/mu));
}


bool HitMiss_gaus(double xMin, double xMax, double yMin, double yMax)
{
	double x = 0., y = 0.;
	x = rand_range(xMin, xMax);
	y = rand_range(yMin, yMax);
	if(y < f_Gaus(x, 0., 1.)) return true;
	else return false;
}


double MC_gaus(double xMin, double xMax)
{
 	double x = 0., y = 0.;
 	x = rand_range(xMin, xMax);
 	y = f_Gaus(x, 0., 1.);
 	return y;
}


double media(double numeri[], int N)
{	
	
	double somma = 0;
	double MEDIA = 0;
	for (int j = 0; j < N; j++){
		somma += numeri[j];
	} 
	MEDIA = somma/N;
	return MEDIA;
}


double media_puntatori(double* num, int n)
{
	double avg = 0;
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


double rand_CLT(double xMin, double xMax, int tries)
{
	double x=0.;
	for (int i=0; i<tries; i++)
		x += rand_range(xMin, xMax);
	return x/tries;
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


double rand_TAC_gaus (double mu, double sigma)
{
 	double xMin = mu - 5*sigma;
 	double xMax = mu + 5*sigma;
 	double yMin = 0.;
 	double yMax = 1./sqrt(2*M_PI*sigma*sigma);
 	double x=0., y=0.;
	do
	{
		x = rand_range(xMin, xMax);
		y = rand_range(yMin, yMax);
	} while (y > f_Gaus(x, mu, sigma));
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


double varianza(double numeri[], double media, int N)
{
	double sommaquadrati = 0;
	double scarto = 0;
	double VARIANZA = 0;
	for (int j = 0; j < N; j++){
		scarto = (media - numeri[j]);
		sommaquadrati += pow(scarto, 2);
	} 
	VARIANZA = sommaquadrati/N;
	return VARIANZA;
}	
