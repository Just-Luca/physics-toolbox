#ifndef __SimpleArr_h
#define __SimpleArr_h

template <class T>
class SimpleArray
{
	private:
	int elementsNum_p;
	T* elements_p;

	public:
	//default costructor
	SimpleArray()
	{
		elements_p = NULL;
		elementsNum_p = 0;
	}
	
	SimpleArray(const int& elem)
	{
		elements_p = new T[1];
		elementsNum_p = 1;
	}
	
	//destructor
	~SimpleArray()
	{
		delete[] elements_p;
	}
	
	//metodo size
	int size()
	{
		return elementsNum_p;
	}

	//costructor
	//SimpleArray(const int& elementsNum);
	
	//copy constructor
	//SimpleArray(const T& original);
	

	
	//metodo element
	//T& element(const int& i);
	

	//operator[]
	//T& operator[](const int& i);
	
	//metodo push
	//void push(T elem);

};

#endif
