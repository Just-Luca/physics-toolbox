// c++ -o esempio06 esempio06.cpp
// ./esempio06 testo.txt

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

int main(int argc, char** argv)
{
	string filename = argv[1];

	ifstream InFile (filename.c_str());
	// metodo good() per verificare che sia possibile leggere il file
	if (InFile.good()==0)  {
		cout << "Errore! Non è possibile aprire il file "<< filename <<endl;
		return 1;
	}
	
	// uso il metodo getline (istream& is, string& str)
	// per leggere il file una riga alla volta 
	//(restituisce falso alla fine del file)
	
	string line, parola;
	stringstream ss;
	int nRighe=0;
	while (getline(InFile, line))
	{
		nRighe++;
		cout << "\nRiga " << nRighe << ": "<< line << endl;
		cout << "Selezione parole pari: ";
		int nParole=0;
		ss << line; // riempio lo stringstream con la riga
		while (ss >> parola) // leggo parola per parola
		{
			nParole ++ ;
			if ((nParole%2) == 0)
				cout << parola << " ";
			else continue;
		}
		cout << endl;
		ss.clear(); // svuoto lo stringstream
	}	
	
	return 0;
}


