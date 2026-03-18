#ifndef dataset_h
#define dataset_h

#include <string>
#include <vector>

using namespace std;
 
class dataset {
 
        public:        
        dataset(); // default constructor (inizializza le variabili private a 0)
    
        dataset(const char* nomefile); 
    
        ~dataset(); //distruttore 
 
	    //metodi
        double GetMedia ();
        double GetDevstd ();
        int GetNdati ();
        int GetDato(const int& i);
        double GetMin();
        double GetMax();
 
        //variabili private
        private:
		int Ndati_p;
		vector <int> dati_p;
		double media_p;
		double devstd_p;
		double min_p;
		double max_p;
 
};
 
#endif

