#include "istogramma.h"
#include <iostream>
#include <iomanip>
#include <cmath>

//costruttore
istogramma::istogramma(int Nbin, float min, float max) {
	Nbin_p = Nbin;
	min_p = min;
	max_p = max;
	step_p = (max_p-min_p)/Nbin_p;
	binContent_p = new int [Nbin_p];
	for (int i=0; i<Nbin_p; i++) binContent_p[i]=0;
	underflow_p = 0; //conteggi sotto min
	overflow_p = 0; //conteggi sopra max
	entries_p = 0; // conteggi totali tra min e max
	sum_p = 0.; //somma di tutti i valori inseriti nell'istogramma
	sumSq_p = 0.; //somma dei quadrati
	std::cout<<"Ho costruito l'istogramma!!!"<<std::endl;	
}

//default constructor
istogramma::istogramma(){
	Nbin_p = 0;
	min_p = 0.;
	max_p = 0.;
	step_p = 0.;
	binContent_p = NULL;
	underflow_p = 0; 
	overflow_p = 0; 
	entries_p = 0; 
	sum_p = 0.; 
	sumSq_p = 0.; 
	std::cout<<"Default constructor!!!"<<std::endl;	
}

//copy constructor
istogramma::istogramma(const istogramma& original){
	Nbin_p = original.Nbin_p;
	min_p = original.min_p;
	max_p = original.max_p;
	step_p = original.step_p;
	binContent_p = new int [Nbin_p];
	for (int i=0; i<Nbin_p; i++) binContent_p[i]=original.binContent_p[i];
	underflow_p = original.underflow_p; 
	overflow_p = original.overflow_p; 
	entries_p = original.entries_p;
	sum_p = original.sum_p; 
	sumSq_p = original.sumSq_p; 
	std::cout<<"Copy constructor!!!"<<std::endl;
}

//distruttore
istogramma::~istogramma() {
	delete [] binContent_p;
	std::cout<<"Ho distrutto l'istogramma!!!"<<std::endl;
}

//operator =
istogramma& istogramma::operator=(const istogramma& original){
	Nbin_p = original.Nbin_p;
	min_p = original.min_p;
	max_p = original.max_p;
	step_p = original.step_p;
	binContent_p = new int [Nbin_p];
	for (int i=0; i<Nbin_p; i++) 
		binContent_p[i]=original.binContent_p[i];
	underflow_p = original.underflow_p; 
	overflow_p = original.overflow_p; 
	entries_p = original.entries_p;
	sum_p = original.sum_p; 
	sumSq_p = original.sumSq_p; 
	std::cout<<"Operator ="<<std::endl;
	return *this;
}

//operator+
istogramma istogramma::operator+(const istogramma& histo2){
	// creo un nuovo istogramma, identico a histo2
	istogramma SumHisto (histo2);
	//
	if (Nbin_p != histo2.Nbin_p || min_p != histo2.min_p || max_p != histo2.max_p) {
		std::cout<<"Errore! I due istogrammi hanno binning differente!\n";
		return SumHisto;
	}
	
	SumHisto.underflow_p += underflow_p; 
	SumHisto.overflow_p += overflow_p; 
	SumHisto.entries_p += entries_p;
	SumHisto.sum_p += sum_p; 
	SumHisto.sumSq_p += sumSq_p; 
	
	for (int i=0; i<Nbin_p; i++) 
		SumHisto.binContent_p[i] += binContent_p[i];

	return SumHisto;
}



int istogramma::Fill (float value) {
	if (value<min_p) {
		underflow_p++;
		return -1;
	}
	else if (value>=max_p) {
		overflow_p++;
		return -1;
	}
	else {
		int bin; // indice del bin da incrementare
		bin = (value-min_p)/step_p;
		binContent_p[bin]++;
		entries_p++;
		sum_p += value;
		sumSq_p += value*value;
		return bin;		
	}	
}

float istogramma::GetMean () const {
	return sum_p/entries_p;
}

float istogramma::GetRMS () const {
	return sqrt(sumSq_p/entries_p - GetMean()*GetMean());
}



void istogramma::Print() const
{
  // cerca il bin con il numero massimo di conteggi
  int max = 0;
  for (int i = 0; i < Nbin_p; ++i)  {
    if (binContent_p[i] > max) max = binContent_p[i] ;
  }
  
  // fattore di rinormalizzazione per la rappresentazione dell'istogramma
  int scale = 50; 
  
  // disegna l'asse y
  std::cout << "        +---------------------------------------------------------------->" 
  	    << std::endl;
  
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














