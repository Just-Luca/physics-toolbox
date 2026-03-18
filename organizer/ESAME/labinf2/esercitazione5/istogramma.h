#ifndef istogramma_h
#define istogramma_h

class istogramma
{
	public:
	//costruttore
	istogramma(int Nbin, float min, float max);
	
	//distruttore
	~istogramma();
	
	//metodi della classe
	int Fill (float value);
	void Print () const;
	float GetMean () const;	//restituisce la media dei valori inseriti
	float GetRMS () const;	//restituisce la dev. std. dei valori inseriti
	int GetMax() const;
	double GetIntegral() const;
	int GetUnderflow() const;
	int GetOverflow() const;
	double GetBinCenter(int i) const;
	int GetBinContent(int i) const;
	 
	private:
	int Nbin_p;
	float min_p;
	float max_p;
	float step_p;		//ampiezza del bin
	int *binContent_p;	//array che contiene i conteggi nei bin
	int underflow_p;	//conteggi sotto min
	int overflow_p;		//conteggi sopra max
	int entries_p;		//conteggi totali tra min e max
	float sum_p;		//somma di tutti i valori inseriti nell'istogramma
	float sumSq_p;		//somma dei quadrati	
};

#endif




