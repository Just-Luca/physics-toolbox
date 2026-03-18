/**
c++ -o vector vector.cpp
*/

#include <iostream>
#include <vector>

int main ()
{
  // definisco un vector
  std::vector<double> MyVector ;
  
  // riempio il vector
  for (int i=0 ; i<10 ; ++i)
  	MyVector.push_back (i * 3.14) ;
  
  // richiedo la dimensione del vector
  std::cout << "Numero elementi = " << MyVector.size() << std::endl; 
    
  // posso accedere agli elementi del vector con []
  for (int i = 0; i < MyVector.size(); i++)
  	std::cout <<"Elemento "<<i << ": " << MyVector[i] << std::endl;  

  return 0 ;
}


