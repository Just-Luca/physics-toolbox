// Default
template<typename T>
SimpleLinkedList<T>::SimpleLinkedList()
{
  elementsNum_p = 0;
  header_p      = NULL;
}

// Constructor
template<typename T>
SimpleLinkedList<T>::SimpleLinkedList(const unsigned int& elementsNum)
{
  elementsNum_p = 0;
  header_p      = NULL;

  for (unsigned int i = 0; i < elementsNum; i++) this->push(0);
}

// Copy Ctor
template<typename T>
SimpleLinkedList<T>::SimpleLinkedList(const SimpleLinkedList<T>& original)
{
  elementsNum_p = 0;
  header_p      = NULL;

  for (unsigned int i = 0; i < original.elementsNum_p; i++) this->push(original[i]);
}

// Destructor
template<typename T>
SimpleLinkedList<T>::~SimpleLinkedList()
{
  for (unsigned int i = 0; i < elementsNum_p; i++) this->pop(0);
}

// Method that returns an element of the array
template<typename T>
T& SimpleLinkedList<T>::element(const unsigned int& i) const
{
  return this->operator[](i);
}

// Overloading operator[]
template<typename T>
T& SimpleLinkedList<T>::operator[](const unsigned int& i) const
{
  struct element* elements = header_p;
  for (unsigned int j = 0; j < elementsNum_p && j != i; j++) elements = elements->next;
  return elements->val;
}

// Size method
template<typename T>
unsigned int SimpleLinkedList<T>::size()
{
  return elementsNum_p;
}

// Push method
template<typename T>
void SimpleLinkedList<T>::push(const T& elem)
{
  // Memory space allocation for an array with one element more
  struct element* newEle = new struct element;
  newEle->val            = elem;
  newEle->next           = NULL;

  // Add the new element
  if (elementsNum_p != 0)
    {
      struct element* elements = header_p;
      for (unsigned int j = 0; j < elementsNum_p-1; j++) elements = elements->next;
      elements->next = newEle;
    }
  else header_p = newEle;

  elementsNum_p++; // Increment the number of elements
}

// Pop method
template<typename T>
T SimpleLinkedList<T>::pop(const unsigned int i)
{
  if (i < elementsNum_p)
    {
      struct element* elements = header_p;

      if (i != 0)
        {
          struct element* previous = NULL;

          for (unsigned int j = 0; j < elementsNum_p && j != i; j++)
            {
              previous = elements;
              elements = elements->next;
            }

          // Update the address pointed by the previous elemenet with the next one
          previous->next = elements->next;
        }
      // Update the address pointed by the previous elemenet with the next one
      else header_p = elements->next;

      T elem = elements->val; // Element to be extracted
      elementsNum_p--; // Decrement the number of elements
      delete elements;

      return elem;
    }
  else
    {
      std::cout << "Error: it's not possible to extract the element number " << i << " from the array" << std::endl;
      std::cout << "Number of elements in the array = " << elementsNum_p << std::endl;
      return header_p->val; // Sine we need to return an element of type T, we choose to return the first one
    }
}
