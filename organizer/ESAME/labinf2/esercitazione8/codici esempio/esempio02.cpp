// c++ -o esempio02 esempio02.cpp

#include <iostream>     
#include <fstream> 
#include <string>

int main (int argc, char** argv) {
	
	if (argc < 2) {  // verifico che venga passato almeno un parametro da riga di comando
		std::cout << "Digitare il nome del file da riga di comando!\n";
		std::cout << "\t./esempio02 File.txt\n";
		return 1;
	}

	std::string NomeFile = argv[1]; // uso un oggetto string per memorizzare il nome del file
	
	std::ofstream OutFile (NomeFile.c_str()); 
	// con il metodo c_str() converto la string in char*, perché i costruttori di 
	// ifstream/ofstream prendono in input un puntatore a char
	
	int a = 12;
	double b = 24.5;
	
	OutFile << a << "    "<< b << std::endl; 
	OutFile.close(); 
	
	
	int x=0;
	double y=0;
	
	std::ifstream InFile (argv[1]); 
	// come parametro di input per i costruttori di ifstream/ofstream 
	// posso anche usare argv[1] (che è già char*) al posto di NomeFile.c_str()
	
	InFile >> x >> y;
	InFile.close();
	
	std::cout << "Il file " << NomeFile <<
		" contiene i numeri: "<< x <<" e " << y << std::endl;

	return 0;
}
