#include <iostream>
#include "SimpleArray.h"

//default constructor
template <class T>
SimpleArray<T>::SimpleArray()
{
	elements_p = NULL;
	elementsNum_p = 0;
}

template <class T>
SimpleArray<T>::~SimpleArray()
{
	delete[] elements_p;
}

//metodo size
template <class T>
int SimpleArray<T>::size()
{
	return elementsNum_p;
}

/*
//constructor
template <class T>
SimpleArray<T>::SimpleArray(const int& elementsNum)
{
	elementsNum_p = elementsNum;
	elements_p = new T[elementsNum];
}

//copy constructor
template <class T>
SimpleArray<T>::SimpleArray(const T& original)
{
	elementsNum_p = original.elementNum_p;
	elements_p = new T[elementsNum_p];
	elements_p = original.elements_p;
}

//destructor
template <class T>
SimpleArray<T>::~SimpleArray()
{
	delete[] elements_p;
}
*/
/******************************************************************************/


/*
//metodo element
template <class T>
SimpleArray<T>::element(const int& i)
{
	if(i < elementsNum_p)
		return elements_p[i];
	else 
		return elements_p[elementsNum_p - 1];
}



//operator[]
template <class T>
SimpleArray<T>::operator[](const int& i)
{
	if(i < elementsNum_p)
		return elements_p[i];
	else 
		return elements_p[elementsNum_p - 1];
}

//metodo push
template <class T>
SimpleArray<T>::push(T elem)
{
	elementsNum_p ++;
	newArray = new T[elementsNum_p];
	
	newArray = elements_p;
	newArray[elementsNum_p - 1] = elem;
}

*/

