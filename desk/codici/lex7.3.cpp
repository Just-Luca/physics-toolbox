#include <string>
#include <iostream>
#include <vector>

using namespace std;

int main () {

	std::vector<char> alfabeto;
	
	for (int i = 0; i < 26; ++i) {
		alfabeto.push_back(65 + i);
	}
	
	std::vector<std::string> frase;
	
	std::string parola;
	std::string parola2 ("***");
	
	std::cout << "" << std::endl;
	
	std::cout << "Inserisci una frase in BOOMERese, e terminala con (spazio)***: " << 		std::endl;
	
	std::cout << "" << std::endl;
	
	std::cout << "	- "; 
	
	std::cin >> parola;
	
	while (parola != parola2) {
		
		frase.push_back(parola);
		std::cin >> parola;
	}
	
	std::string periodo;
	
	for (int r = 0; r < frase.size(); ++r) 
	{
		periodo += frase[r];
	}
	
	std::cout << "" << std::endl;
	
	char a,b;
	
	if (frase.size() == 1) {
		
		a = 'a';
	} else a = 'e';
	
	if (periodo.length() == 1) {
		
		b = 'a';
	} else b = 'e';
	
	
	std::cout << "Nella frase ci sono " << frase.size() << " parol" << a << " e " 
		    << periodo.length() << " letter" << b << ", di cui:" << std::endl;
		    
	std::cout << "" << std::endl;
	
	for (int t = 0; t < 26; ++t) {
	
		int k = 0;
			
		for (int z = 0; z < periodo.length(); ++z) {
			
			if (alfabeto[t] == periodo[z]) { 
				++k;
			};
		}
		
		std::cout << "-) " << k << " " 
			    << alfabeto[t] << std::endl;
	}
	
	std::cout << "" << std::endl;
	
	return 0;
}

