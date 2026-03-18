// Default
template<typename T>
SimpleArray<T>::SimpleArray()
{
  elementsNum_p = 0;
}

// Costruttore
template<typename T>
SimpleArray<T>::SimpleArray(const int& elementsNum)
{
  elementsNum_p = elementsNum;
  if (elementsNum_p != 0)
    {
      std::unique_ptr<T[]> tmp(new T[elementsNum]);
      elements_p = std::move(tmp);
    }
}

// Copy Ctor
template<typename T>
SimpleArray<T>::SimpleArray(const SimpleArray<T>& original)
{
  elementsNum_p = original.elementsNum_p;
  if (elementsNum_p != 0)
    {
      std::unique_ptr<T[]> tmp(new T[elementsNum_p]);
      elements_p = std::move(tmp);
      for (int i = 0; i < elementsNum_p; i++)
      elements_p[i] = original.elements_p[i];
    }
}

// Distruttore
template<typename T>
SimpleArray<T>::~SimpleArray() {}

// Metodo che restituisce un elemento dell'array
template<typename T>
T& SimpleArray<T>::element(const int& i)
{
  if (i < elementsNum_p) return elements_p[i];
  else                   return elements_p[elementsNum_p - 1];
}

// Overloading operator[]
template<typename T>
T& SimpleArray<T>::operator[](const int& i)
{
  if (i < elementsNum_p) return elements_p[i];
  else                   return elements_p[elementsNum_p - 1];
}

// Metodo size
template<typename T>
int SimpleArray<T>::size()
{
  return elementsNum_p;
}

// Metodo push
template<typename T>
void SimpleArray<T>::push(const T& elem)
{
  elementsNum_p++; // Incrementa il numero degli elementi

  // Alloca lo spazio di memoria per ospitare un array con un elemento in piu`
  std::unique_ptr<T[]> newAddress(new T[elementsNum_p]);

  for (int i = 0; i < (elementsNum_p-1); i++) // Copia tutti gli elementi dell'array nel nuovo spazio di memoria
    newAddress[i] = elements_p[i];

  newAddress[elementsNum_p-1] = elem; // Aggiunge in coda l'elemento passato in input

  // Aggiorna l'indirizzo di elements_p in modo che punti all'indirizzo del nuovo array
  elements_p = std::move(newAddress);

  return;
}

// Metodo pop
template<typename T>
T SimpleArray<T>::pop(const int& i)
{
  if (i < elementsNum_p)
    {
      T elem = elements_p[i]; // Elemento da estrarre e passare in uscita
      elementsNum_p--; // Decrementa il numero degli elementi

      // Alloca lo spazio di memoria per ospitare un array con un elemento in meno
      std::unique_ptr<T[]> newAddress(new T[elementsNum_p]);

      for (int j = 0; j < i; j++)
        newAddress[j] = elements_p[j];

      for (int j = (i+1); j < (elementsNum_p+1); j++)
        newAddress[j-1] = elements_p[j];

      // Aggiorna l'indirizzo di elements_p in modo che punti all'indirizzo del nuovo array
      elements_p = std::move(newAddress);

      return elem;
    }
  else
    {
      std::cout << "Errore: non è possibile estrarre l'elemento numero " << i << " dell'array" << std::endl;
      std::cout << "N elementi array = " << elementsNum_p << std::endl;
      return elements_p[0]; // Deve comunque restituire un elemento di tipo T, sceglie ad esempio il primo
    }
}
