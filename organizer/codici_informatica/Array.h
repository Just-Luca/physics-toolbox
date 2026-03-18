#ifndef simpleArr_h
#define simpleArr_h  

template <class T> 
class SimpleArray {
 
	public:
		//costruttore
		SimpleArray(const int& elementsNum) {
			elementsNum_p = elementsNum;
			elements_p = new T[elementsNum];
		}
		
		//default
		SimpleArray() {
			elementsNum_p = 0;
			elements_p = 0;				
		}
		
		//copy
		SimpleArray(const SimpleArray &original) {
			elementsNum_p = original.elementsNum_p;
			elements_p = original.elements_p;
		}
		
		//distruttore
		~SimpleArray() {
			delete[] elements_p;
		}
	
		//metodo che restituisce un elemento dell'array 
		T& element(const int &i) {
			if(i <= elementsNum_p) return elements_p[i];
			else std::cout << "L'elemento non è nel vettore" << std::endl;
		}
		
		//rilettura
		void rilettura () {
			for(int i = 0; i < elementsNum_p; ++i) {
				std::cout << "elemento " << i << " = " << element(i) 
					    << std::endl;
			}
		}
		
		//size
		int size() {
			return elementsNum_p;
		}
		
		//push
		void push (T elem) {
			
			T * newelement = (T *) malloc (sizeof(T)*(elementsNum_p + 1));
			for (int i = 0; i < elementsNum_p; i++) {
			
				newelement[i] = elements_p[i];
			}
			
			free (elements_p);
			elements_p = newelement;
			
			elementsNum_p++;
			elements_p[elementsNum_p-1] = elem;
			
		}
		
		//pop
		T pop(int i) {
		
			T * newelement = (T *) malloc (sizeof(T)*(elementsNum_p - 1));
			
			for (int t = 0, k = 0; t < elementsNum_p; t++) {
				
				if ( i != t) {
				
					newelement[k] = elements_p[t];
					k++; 
				};
			}
		 
			/*for(i; i < elementsNum_p; i++) {
				element(i) = element(i+1);
			}*/
			
			free (elements_p);
			elements_p = newelement;
			
			elementsNum_p = elementsNum_p - 1;
			
			return 0;
		}
				
		//overloading operator[]
		T& operator[](const int &i)  {
			if(i < elementsNum_p) return elements_p[i];
			else return elements_p[elementsNum_p - 1];
		} 
 
	private: 
		int elementsNum_p;
		T* elements_p; 
};

#endif



