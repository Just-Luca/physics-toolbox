// c++ -o esempio03 esempio03.cpp

#include <iostream>     
#include <fstream> 
#include <string>

int main (int argc, char** argv) {
	
	if (argc < 2) {  // verifico che venga passato almeno un parametro da riga di comando
		std::cout << "Digitare il nome del file da riga di comando!\n";
		std::cout << "\t./esempio03 DataFile.txt\n";
		return 1;
	}

	std::string NomeFile = argv[1]; 	
	std::ofstream OutFile (NomeFile.c_str()); 
	
	for (int i=0; i<10; i++) {
		OutFile << i*2 << "\t" << i*2+1<<std::endl;
	}
	OutFile.close();
	
	
	int x=0;
	int y=0;
	int Nrighe=0;
	
	std::ifstream InFile (NomeFile.c_str()); 
	while (true) {	// imposto un loop infinito, che verrà interrotto con l'istruzione break
		InFile >> x >> y;
		if (InFile.eof()==true) // il metodo eof() restituisce true alla fine del file
			break;
		
		std::cout << x << "\t" << y << std::endl;
		Nrighe++;
	}
	InFile.close();
	
	std::cout << "Il file " << NomeFile <<
		" contiene " << Nrighe << " righe"<< std::endl;

	return 0;
}
