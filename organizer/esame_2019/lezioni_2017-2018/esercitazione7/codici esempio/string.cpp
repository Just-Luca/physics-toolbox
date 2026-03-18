// c++ -o string string.cpp

#include <string>
#include <iostream>

int main()	
{
  std::string frase = "W la pizza";
  
  int lunghezza = frase.length();
  std::cout << "Lunghezza frase: " << lunghezza << std::endl; 
  
  const char* fraseC = frase.c_str();
  std::cout << fraseC << std::endl; 
  
  std::string parola ("pizza");
  int posizione = frase.find(parola);
  std::cout << "La parola " << parola <<
	  " si trova in posizione " << posizione << std::endl;
  
  std::string parola2 ("pozza");
  int confronto = parola2.compare(parola);
  if (confronto == 0) std::cout << "Le due parole sono uguali" << std::endl;
  else std::cout << "Le due parole sono diverse" << std::endl;
  
  for (int i=0; i<parola2.length(); i++)
  	std::cout << "Carattere "<<i<<": "<< parola2[i] << std::endl;
  
  return 0;
}
