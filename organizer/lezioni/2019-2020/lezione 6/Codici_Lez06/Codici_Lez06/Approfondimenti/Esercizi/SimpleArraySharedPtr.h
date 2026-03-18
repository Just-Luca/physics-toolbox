#ifndef SIMPLEARR_H
#define SIMPLEARR_H

template <class T>
class SimpleArray
{
public:
  // Default
  SimpleArray();

  // Costruttore
  SimpleArray(const int& elementsNum);

  // Copy Ctor
  SimpleArray(const SimpleArray& original);

  // Distruttore
  ~SimpleArray();

  // Metodo che restituisce un elemento dell'array
  T& element(const int& i);

  // Overloading operator[]
  T& operator[](const int& i);

  // Metodo size
  int size();

  // Metodo push
  void push(const T& elem);

  // Metodo pop
  T pop(const int& i);

private:
  int elementsNum_p;
  std::shared_ptr<T> elements_p;
};

#include "SimpleArraySharedPtr.tcc"
#endif
