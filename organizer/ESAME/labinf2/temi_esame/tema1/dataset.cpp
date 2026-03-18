#include <cstdlib>
#include <cmath>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "dataset.h"

//default constructor
dataset::dataset()
{
	N_p = 0;
	mu_p = 0;
	dati_p.push_back(0);
	media_p = 0;
	devstd_p = 0;
}

//constructor
dataset::dataset(const char* nomefile)
{
	std::ifstream inF;
    inF.open(nomefile);
    int N = 0;
    while(1)
    {
        int x = 0;
        inF >> x;
        if(inF.eof()) break;
        dati_p.push_back(x);
        N++;
    }
    
	N_p = N;
	mu_p = 0;
	media_p = 0;
	devstd_p = 0;
}

//destructor
dataset::~dataset() {}

/******************************************************************************************************************************/

//metodo GetMedia
double dataset::GetMedia ()
{
	double somma = 0;
	for (int j = 0; j < N_p; j++)
		somma += (double)dati_p[j];
	
	media_p = somma/N_p;
	return media_p;
}

//metodo GetDevstd
double dataset::GetDevstd ()
{
	double sommaquadrati = 0, scarto = 0;
	for (int j = 0; j < N_p; j++)
	{
		scarto = (media_p - dati_p[j]);
		sommaquadrati += pow(scarto, 2);
	}
	 
	devstd_p = sqrt(sommaquadrati/(N_p-1));
	return devstd_p;
}

//metodo GetNdati
int dataset::GetNdati ()
{
	return N_p;
}

//metodo GetDato
int dataset::GetDato (const int& i)
{
	return dati_p[i];
}

