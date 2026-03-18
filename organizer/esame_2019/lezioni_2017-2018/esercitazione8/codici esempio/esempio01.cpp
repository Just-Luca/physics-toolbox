// c++ -o esempio01 esempio01.cpp

#include <iostream>     
#include <fstream> 
#include <string> 

int main () {

	const char *filename = "File.txt";
	
	// costruisco un oggetto di tipo ofstream passando come parametro di input 
	// il nome del file su cui verrà scritto l'output
	std::ofstream OutFile (filename); 
	
	int a = 12;
	double b = 24.5;
	char parola [] = "ciao";
	
	OutFile << a << "    "<< b << std::endl; // scrivo in output i valori delle variabili a e b
	OutFile << parola << std::endl;
	OutFile.close(); // chiudo il file
	
	
	int x=0;
	double y=0;
	std::string word;
	
	std::ifstream InFile (filename);  // apro il file "File.txt" in modalità lettura
	
	InFile >> x >> y; // leggo i numeri contenuti nel file e li memorizzo nelle variabili x e y
	InFile >> word;
	InFile.close();
	
	std::cout << "Il file " << filename <<
		" contiene i numeri: "<< x <<" e " << y << std::endl;
	std::cout << "e la parola: "<< word << std::endl;

	return 0;
}



