// Default
template<typename T>
SimpleArray<T>::SimpleArray()
{
  elementsNum_p = 0;
  elements_p    = NULL;
}

// Constructor
template<typename T>
SimpleArray<T>::SimpleArray(const unsigned int& elementsNum)
{
  elementsNum_p = 0;
  elements_p    = NULL;

  for (unsigned int i = 0; i < elementsNum_p; i++) this->push(0);
}

// Copy Ctor
template<typename T>
SimpleArray<T>::SimpleArray(const SimpleArray<T>& original)
{
  elementsNum_p = 0;
  elements_p    = NULL;

  for (unsigned int i = 0; i < original.elementsNum_p; i++) this->push(original[i]);
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
  this->operator[](i);
}

// Overloading operator[]
template<typename T>
T& SimpleArray<T>::operator[](const unsigned int& i) const
{
  if (i < elementsNum_p) return elements_p[i];
  else                   return elements_p[elementsNum_p - 1];
}

// Size method
template<typename T>
unsigned int SimpleArray<T>::size() const
{
  return elementsNum_p;
}

// Push method
template<typename T>
void SimpleArray<T>::push(const T& elem)
{
  elementsNum_p++; // Increment the number of elements

  // Memory space allocation for an array with one element more
  T* newAddress = new T[elementsNum_p];

  for (unsigned int i = 0; i < (elementsNum_p-1); i++) // Copy all array elements in the new array
    newAddress[i] = elements_p[i];

  newAddress[elementsNum_p-1] = elem; // Add the new element

  delete [] elements_p; // Free the memory of the old array

  // Update the address of elements_p in such a way that it points to the new array
  elements_p = newAddress;
}

// Pop method
template<typename T>
T SimpleArray<T>::pop(const unsigned int& i)
{
  if (i < elementsNum_p)
    {
      T elem = elements_p[i]; // Element to be extracted
      elementsNum_p--; // Decrement the number of elements

      // Memory space allocation for an array with one element less
      T* newAddress = new T[elementsNum_p];

      for (unsigned int j = 0; j < i; j++)
        newAddress[j] = elements_p[j];

      for (unsigned int j = (i+1); j < (elementsNum_p+1); j++)
        newAddress[j-1] = elements_p[j];

      delete [] elements_p; // Free the memory of the old array

      // Update the address of elements_p in such a way that it points to the new array
      elements_p = newAddress;

      return elem;
    }
  else
    {
      std::cout << "Error: it's not possible to extract the element number " << i << " from the array" << std::endl;
      std::cout << "Number of elements in the array = " << elementsNum_p << std::endl;
      return elements_p[0]; // Sine we need to return an element of type T, we choose to return the first one
    }
}
