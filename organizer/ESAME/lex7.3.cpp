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
	
	std::cout << "Inserisci una frase: "; 
	
	std::cin >> parola;
	
	while (parola != parola2) {
		
		frase.push_back(parola);
		std::cin >> parola;
	}
	
	std::string periodo;
	
	for (int r = 0; r < frase.size(); ++r) 
	{
		periodo += frase[r];
		//periodo += " ";
	}
	
	std::cout << "" << std::endl;
	//std::cout << periodo << std::endl;
	
	/*for (int i = 0; i<periodo.length(); i++){
		cout << periodo [i] << endl;
	}*/
	
	
	for (int t = 0; t < 26; ++t) {
	
		int k = 0;
			
		for (int z = 0; z < periodo.length(); ++z) {
			
			if (alfabeto[t] == periodo[z]) { 
				++k;
			};
		}
		
		std::cout << "Nella frase ci sono " << k << " " 
			    << alfabeto[t] << std::endl;
	}
	
	return 0;
}

		
