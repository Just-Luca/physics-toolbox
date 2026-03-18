#ifndef simpleArr_h
#define simpleArr_h

template <class T>
class SimpleArray
{
	public:
	//default constructor
	SimpleArray()
	{
		elementsNum_p=0;
      	elements_p = NULL;
	}
		
	//constructor
	SimpleArray(const int& elementsNum)
	{
		elementsNum_p = elementsNum;
		elements_p = new T[elementsNum];
	}
		
	//copy constructor
	SimpleArray(const SimpleArray& original)
	{
		elementsNum_p = original.elementsNum_p;
    	elements_p = new T[elementsNum_p];
    	for (int i = 0; i < elementsNum_p; i++)
			elements_p[i] = original.elements_p[i];
	}
		
	//distruttore
	~SimpleArray() {delete[] elements_p;}

/*****************************************************************************************************************************************/
		
	//metodo che restituisce un elemento dell'array
	T& element(const int& i)
	{
		if(i < elementsNum_p)
			return elements_p[i];
		else return elements_p [elementsNum_p - 1];
	}
	
	//metodo size: restituisce il numero di elementi dell'array
	int size()
	{
		return elementsNum_p;
	}
		
	//metodo push: inserisce un nuovo elemento in coda all'array
	void push(T elem)
	{
		elementsNum_p++; //aumento il numero degli elementi del vettore
			
		//alloco lo spazio di memoria per ospitare l'array con un'entrata in più
		T* newAddress = new T[elementsNum_p]; 	
			
		//copio le entrate del vettore nel nuovo spazio di memoria
		for(int i=0; i<(elementsNum_p - 1); i++)
			newAddress[i] = elements_p[i];
			
		newAddress[elementsNum_p-1] = elem; // Aggiunge in coda l'elemento passato in input
    	delete [] elements_p; // Libera la memoria del vecchio array
		
    	// Aggiorna l'indirizzo di elements_p in modo che punti all'indirizzo del nuovo array
    	elements_p = newAddress;

    	return;
	}
	
	//metodo pop: estrae l'elemento i-esimo e shifta gli altri elementi per colmare il buco rimasto
	T pop(int i) 
	{
	    if (i < elementsNum_p)
	    {
			T elem = elements_p[i]; // Elemento da estrarre e passare in uscita
	    	elementsNum_p--;
	    	T* newAddress = new T[elementsNum_p];
			
	    	for (int j = 0; j < i; j++)
				newAddress[j] = elements_p[j];
				
    		for (int j = (i+1); j < (elementsNum_p+1); j++)
				newAddress[j-1] = elements_p[j];
    		delete [] elements_p;
    		elements_p = newAddress;
    		return elem;
		}	
		else
		{
			std::cout << "Errore: non è possibile estrarre l'elemento numero " << i << " dell'array" << std::endl;
			std::cout << "N elementi array = " << elementsNum_p << std::endl;
			return elements_p[0]; // Deve comunque restituire un elemento di tipo T, sceglie ad esempio il primo
    	}
	}

/***************************************************************************************************************************************/
		
	//operatore
	T& operator[](const int& i)
	{
		if(i < elementsNum_p)
			return elements_p[i];
		else return elements_p [elementsNum_p - 1];
	}
		
	private:
	int elementsNum_p;
	T* elements_p; 		
};

#endif

