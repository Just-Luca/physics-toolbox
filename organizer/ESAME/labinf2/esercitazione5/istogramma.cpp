#include "istogramma.h"
#include <iostream>
#include <iomanip>
#include <cmath>

//costruttore
istogramma::istogramma(int Nbin, float min, float max)
{
	Nbin_p = Nbin;
	min_p = min;
	max_p = max;
	step_p = (max_p-min_p)/Nbin_p;
	binContent_p = new int [Nbin_p];
	
	for (int i=0; i<Nbin_p; i++)
		binContent_p[i]=0;
		
	underflow_p = 0; //conteggi sotto min
	overflow_p = 0; //conteggi sopra max
	entries_p = 0; // conteggi totali tra min e max
	sum_p = 0.; //somma di tutti i valori inseriti nell'istogramma
	sumSq_p = 0.; //somma dei quadrati
}

//distruttore
istogramma::~istogramma()
{
	delete [] binContent_p;
}

//***************************************************************************************************************************//

int istogramma::Fill(float value)
{
	if (value < min_p)
	{
		underflow_p++;
		return -1;
	}
	else if (value >= max_p)
	{
		overflow_p++;
		return -1;
	}
	else
	{
		int bin; // indice del bin da incrementare
		bin = (value-min_p)/step_p;
		binContent_p[bin]++;
		entries_p++;
		sum_p += value;
		sumSq_p += value*value;
		return bin;		
	}	
}

//**************************************************************************************************************************//

void istogramma::Print() const
{
 	// cerca il bin con il numero massimo di conteggi
	int max = 0;
	for (int i = 0; i < Nbin_p; ++i)
	{
    	if (binContent_p[i] > max)
    		max = binContent_p[i];
	}
  
 	// fattore di rinormalizzazione per la rappresentazione dell'istogramma
  	int scale = 50; 
  
  	// disegna l'asse y
  	std::cout << "        +---------------------------------------------------------------->" << std::endl;
  
	// disegna il contenuto dei bin
  	for (int i = 0; i < Nbin_p; ++i)
    {
    	std::cout << std::fixed << std::setw(8) << std::setprecision(2) << min_p + i * step_p <<"|";
    	int freq = int(scale * binContent_p[i] / max);
    	for (int j = 0; j < freq; ++j)
    	    std::cout << "#";
      
    	std::cout << std::endl;
    }
  	std::cout << "        |\n" << std::endl;
}

//********************************************************************************************************************************//

float istogramma::GetMean () const
{
	return sum_p/entries_p;
}

//*******************************************************************************************************************************//

float istogramma::GetRMS () const
{
	return sqrt(sumSq_p/entries_p - GetMean()*GetMean());
}

//*******************************************************************************************************************************//

int istogramma::GetMax() const
{
	int max=0;
	for (int i=0; i<Nbin_p; ++i) 
	{
	    if (binContent_p[i] > max) 
	    	max = binContent_p[i] ;
	}
	return max;
}

//******************************************************************************************************************************//

double istogramma::GetIntegral() const
{
	return entries_p*step_p;
}

//*****************************************************************************************************************************//

int istogramma::GetUnderflow() const
{
	return underflow_p;
}

//****************************************************************************************************************************//

int istogramma::GetOverflow() const
{
	return overflow_p;
}

//***************************************************************************************************************************//

double istogramma::GetBinCenter(int i) const
{
	return (0.5+i)*step_p + min_p;
}

//**************************************************************************************************************************//

int istogramma::GetBinContent(int i) const
{
	return binContent_p[i];
}

