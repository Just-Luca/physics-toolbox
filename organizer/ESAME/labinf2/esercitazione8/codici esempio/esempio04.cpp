// c++ -o esempio04 esempio04.cpp
// ./esempio04 DataFile.txt
// DataFile.txt creato con esempio03

#include <iostream>     
#include <fstream> 
#include <string>
#include <vector>

int main (int argc, char** argv) {
	
	if (argc < 2) {  // verifico che venga passato almeno un parametro da riga di comando
		std::cout << "Digitare il nome del file da riga di comando!\n";
		std::cout << "\t./esempio04 DataFile.txt\n";
		return 1;
	}
	std::string filename = argv[1]; 	
	
	int x=0;
	int y=0;
	int Nrighe=0;
	
	std::ifstream InFile (filename.c_str()); 
	
	// metodo good() per verificare che sia possibile leggere il file
	// se il file non è presente nella cartella o non è possibile aprirlo stampo un messaggio di errore
	if (InFile.good()==0)  {
		std::cout << "Errore! Non è possibile aprire il file "<< filename <<std::endl;
		return 1;
	}	
	
	std::vector<int> vec1; // definisco due vector per memorizzare i numeri contenuti nel file
	std::vector<int> vec2; // -> non mi serve sapere a priori quanti numeri dovrò salvare!
	
	while (true) {	// imposto un loop infinito, che verrà interrotto con l'istruzione break
		InFile >> x >> y;
		if (InFile.eof()==true) // il metodo eof() restituisce true alla fine del file
			break;
		
		vec1.push_back(x); 
		vec2.push_back(y);
		Nrighe++;
	}
	InFile.close();
	
	std::cout << "Il file " << filename <<	" contiene "<< Nrighe <<" righe"<< std::endl;
	std::cout << "Il vector vec1 contiene "<< vec1.size() <<" elementi"<< std::endl;
	std::cout << "Il vector vec2 contiene "<< vec2.size() <<" elementi"<< std::endl;
	
	for (int i=0; i<vec1.size(); i++) {
		std::cout << vec1[i] <<"\t" << vec2[i] << std::endl;
	}

	return 0;
}
