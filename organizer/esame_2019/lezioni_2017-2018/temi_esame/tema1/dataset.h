#ifndef dataset_h
#define dataset_h

#include <string>
#include <vector>


class dataset
{
	public:
	dataset(); // default constructor (inizializza le variabili private a 0)
	dataset(const char* nomefile); //constructor
    
	~dataset(); //distruttore 

	//metodi
	double GetMedia ();
	double GetDevstd ();
	int GetNdati ();
	int GetDato(const int& i);
 
	//variabili private
	private:
	int N_p;
	int mu_p;
	std::vector<int> dati_p;
	double media_p;
	double devstd_p;
 
};
 
#endif

