// c++ -o esempio05 esempio05.cpp

#include <iostream>     // std::cout
#include <sstream> // std::stringstream  

using namespace std; 

int main () {

  stringstream ss;
  int anno = 1923;
  string nome = "Jonh";

  // posso unire numeri e stringhe in un unico stream
  ss << nome << " nacque nel " << anno;
  
  // conversione sstream -> string
  string frase = ss.str();
  cout << frase << endl;
  
  return 0;
}
