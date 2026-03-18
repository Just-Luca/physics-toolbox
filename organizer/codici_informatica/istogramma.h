// creo la classe istogramma

#ifndef istogramma_h
#define istogramma_h

class istogramma {

	public:
		istogramma(int nBin, float min, float max); //costruttore
		~istogramma(); //distruttore 
		
		//metodi della classe
		int Fill (float valore);
		void Print () const;
		float GetMean () const; // restituisce la media dei valori inseriti
		float GetRMS () const; // restituisce la deviazione standard dei valori
		void GetUnderflow () const;
		void GetOverflow () const;
		float GetIntegral () const;
		
	private:
		int nBin_p; //_p → ptivate
		float min_p;
		float max_p;
		float step_p; // ampiezza del bin
		int *binContent_p; // array che contiene i conteggi del bin
		int underflow_p; // conteggi sotto min
		int overflow_p; // conteggi sopra max
		int entries_p; // conteggi totali tra min e max;
		float sum_p; // somma di tutti i valori inseriti nell'istogramma
		float sumSq_p; // somma dei quadrati
};

#endif
