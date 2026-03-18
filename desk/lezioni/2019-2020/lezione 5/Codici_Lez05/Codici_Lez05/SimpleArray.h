#ifndef SIMPLEARR_H
#define SIMPLEARR_H

template <class T>
class SimpleArray
{
public:
  // Constructor
  SimpleArray(const unsigned int& elementsNum);

  // Destructor
  ~SimpleArray();

  // Method that returns an element of the array
  T& element(const unsigned int& i) const;

  // Overloading operator[]
  T& operator[](const unsigned int& i) const;

private:
  unsigned int elementsNum_p;
  T* elements_p;
};

#include "SimpleArray.tcc"
#endif
