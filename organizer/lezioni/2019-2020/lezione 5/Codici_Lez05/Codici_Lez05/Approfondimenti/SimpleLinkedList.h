#ifndef SIMPLEARRLINKLIST_H
#define SIMPLEARRLINKLIST_H

template <class T>
class SimpleLinkedList
{
public:
  // Default
  SimpleLinkedList();

  // Costruttore
  SimpleLinkedList(const unsigned int& elementsNum);

  // Copy Ctor
  SimpleLinkedList(const SimpleLinkedList& original);

  // Distruttore
  ~SimpleLinkedList();

  // Metodo che restituisce un elemento dell'array
  T& element(const unsigned int& i) const;

  // Overloading operator[]
  T& operator[](const unsigned int& i) const;

  // Metodo size
  unsigned int size();

  // Metodo push
  void push(const T& elem);

  // Metodo pop
  T pop(const unsigned int i);

private:
  struct element
  {
    element* next;
    T val;
  };

  unsigned int elementsNum_p;
  struct element* header_p;


  // ################################################################
  // # Iterator section which behaves exactly like an std::iterator #
  // ################################################################
public:
  class iterator
  {
  public:
    // ###################
    // # Iterator traits #
    // ###################
    typedef std::forward_iterator_tag iterator_category;
    typedef T value_type;
    typedef int difference_type;
    typedef struct element& reference;
    typedef struct element* pointer;

    iterator(pointer ptr) : ptr_(ptr) {} // Constructor

    iterator operator++()
    {
      ptr_ = ptr_->next;
      return *this;
    } // pre-increment, ++it

    iterator operator++(int junk)
    {
      iterator it = *this;
      ptr_ = ptr_->next;
      return it;
    } // post-increment, it++

    value_type& operator*()  { return ptr_->val;  }
    value_type* operator->() { return *ptr_->val; }

    bool operator==(const iterator& rhs) { return ptr_ == rhs.ptr_; }
    bool operator!=(const iterator& rhs) { return ptr_ != rhs.ptr_; }

  private:
    pointer ptr_;
  };

  iterator begin() { return iterator(header_p); }
  iterator end()
  {
    struct element* elements = header_p;
    for (unsigned int j = 0; j < elementsNum_p; j++) elements = elements->next;
    return iterator(elements);
  }
};

#include "SimpleLinkedList.tcc"
#endif
