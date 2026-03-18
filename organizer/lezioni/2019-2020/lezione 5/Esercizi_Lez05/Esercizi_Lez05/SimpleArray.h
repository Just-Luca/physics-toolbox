#ifndef SIMPLEARR_H
#define SIMPLEARR_H

template <class T>
class SimpleArray
{
public:
  // Default
  SimpleArray();

  // Constructor
  SimpleArray(const unsigned int& elementsNum);

  // Copy Ctor
  SimpleArray(const SimpleArray& original);

  // Destructor
  ~SimpleArray();

  // Method that returns an element of the array
  T& element(const unsigned int& i) const;

  // Overloading operator[]
  T& operator[](const unsigned int& i) const;

  // Size method
  unsigned int size() const;

  // Push method
  void push(const T& elem);

  // Pop method
  T pop(const unsigned int& i);

private:
  unsigned int elementsNum_p;
  T* elements_p;
};

#include "SimpleArray.tcc"
#endif
