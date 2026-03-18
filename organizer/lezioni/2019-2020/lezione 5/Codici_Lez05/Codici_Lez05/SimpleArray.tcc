// Constructor
template<typename T>
SimpleArray<T>::SimpleArray(const unsigned int& elementsNum)
{
  elementsNum_p = elementsNum;
  if (elementsNum_p != 0)
    elements_p = new T[elementsNum];
  else elements_p = NULL;
}

// Destructor
template<typename T>
SimpleArray<T>::~SimpleArray()
{
  delete[] elements_p;
}

// Method that returns an element of the array
template<typename T>
T& SimpleArray<T>::element(const unsigned int& i) const
{
  return this->operator[](i);
}

// Overloading operator[]
template<typename T>
T& SimpleArray<T>::operator[](const unsigned int& i) const
{
  if (i < elementsNum_p) return elements_p[i];
  else                   return elements_p[elementsNum_p - 1];
}
