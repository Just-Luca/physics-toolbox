#ifndef simpleArr_h
#define simpleArr_h  

template <class T>
 
class SimpleArray {

	private: 
		int elementsNum_p;
		T* elements_p; 
 
	public:
		//costruttore
		SimpleArray(const int& elementsNum) {
			elementsNum_p = elementsNum;
			elements_p = new T[elementsNum];
		}
		
		//costruttore default
		SimpleArray() {
			elementsNum_p = 0.;
			elements_p = 0;
		}
		
		//costruttore copy
		SimpleArray(const SimpleArray& original) {
			elementsNum_p = original.elementsNum_p;
			elements_p = original.elements_p;
			
		//distruttore
		~SimpleArray() {
			delete[] elements_p;
		}
	
		//size
		int size() {
			return elementsNum_p;
		}
		
		//push
		//void push (T nuovoE) {
			
			
		//metodo che restituisce un elemento dell'array 
		T& element(const int &i) {
			if(i < e lementsNum_p) return elements_p[i];
			else return elements_p[elementsNum_p - 1];
		}
	
		//overloading operator[]
		T& operator[](const int &i)  {
			if(i < elementsNum_p) return elements_p[i];
			else return elements_p[elementsNum_p - 1];
		} 
};

#endif


