#include <cstdlib>
#include <cmath>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>


#include "dataset.h"

using namespace std;

//defaut constructor
dataset::dataset()
{

	N_p = 0;
	mu_p = 0;
    dati_p.push_back(0);
	media_p = 0;
	devstd_p = 0;

}

//constructor
dataset::dataset(const char* filNam)
{
    ifstream inF;
    inF.open(filNam);
    int N = 0;
    while(1){
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
dataset::~dataset()
{
}


//media
double dataset::GetMedia()
{
	double media = 0;
	
	for (int j=0; j<N_p; j++)
	{
		media = media + (double) dati_p[j];
	}
	media_p = media / N_p;
	return media_p;
}

//dev. std.
double dataset::GetDevstd()
{
	double var = 0;
	double a = 0;

	for(int k=0; k<N_p; k++)
	{
		a = (double) dati_p [k];
		var = var + ((media_p - a)*(media_p-a));
	}
	devstd_p = sqrt(var/(N_p-1));
	return devstd_p;
}

//Numero di estrazioni
int dataset::GetNdati()
{

	return N_p;
}

//il valore di conteggio dell'estrazione i-esima
int dataset::GetDato(const int& i)
{
	return dati_p [i];

}


