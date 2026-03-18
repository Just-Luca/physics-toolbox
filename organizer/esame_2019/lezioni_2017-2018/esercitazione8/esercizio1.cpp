#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

int main(int argc, char** argv)
{
	//verifico che vengano passati almeno due parametri da riga di comando
	if(argc < 3)
	{
		std::cout << "Digitare il nome del file da riga di comando!" << std::endl;
		return 1;
	}
	
	std::string fileInput = argv[1];
	std::string fileOutput = argv[2];
	
	std::ifstream InFile(fileInput.c_str());
	
	if (InFile.good() == 0)
    {
    	std::cout << "Errore! Non è possibile aprire il file "<< fileInput <<std::endl;
    	return -1;
    }
    
    std::vector<double> vec1; // definisco due vector per memorizzare i numeri contenuti nel file
	std::vector<double> vec2; // non mi serve sapere a priori quanti numeri dovrò salvare
  
	double x=0;
	double y=0;
	int Nrighe=0;
  
  while (true)	// imposto un loop infinito, che verrà interrotto con l'istruzione break
    {
    	InFile >> x >> y;
    	if (InFile.eof()==true) // il metodo eof() restituisce true alla fine del file
			break;
		std::cout << x << " " << y << std::endl;
      	vec1.push_back(x); 
      	vec2.push_back(y);
      	Nrighe++;
    }
	InFile.close();
	
	std::cout << "Il file " << fileInput <<	" contiene " << Nrighe << " righe" << std::endl;
	std::cout << "Il vector vec1 contiene "<< vec1.size() << " elementi" << std::endl;
	std::cout << "Il vector vec2 contiene "<< vec2.size() << " elementi" << std::endl;
  	
  	double sum=0., sumSq=0.;
	double mean, devst;
  
	mean = sum/(float)Nrighe;
	devst = sqrt(sumSq/(float)Nrighe - mean*mean);	
  
	std::ofstream OutFile (fileOutput.c_str());
	OutFile << "Prima colonna di dati:" << std::endl;
	OutFile << "Media = " << mean << std::endl;
	OutFile << "Dev.Std = " << devst  << std::endl;
  
	sum=0.; // azzero i contatori
	sumSq=0.;
	for (int i=0; i<vec2.size(); i++)
    {
	    sum += vec2[i];
	    sumSq += vec2[i]*vec2[i];
    }
	mean = sum/(float)Nrighe;
	devst = sqrt(sumSq/(float)Nrighe - mean*mean);	
	OutFile << "Seconda colonna di dati:" << std::endl;
	OutFile << "Media = " << mean << std::endl;
	OutFile << "Dev.Std = " << devst  << std::endl;
	OutFile.close();
  
	return 0;
}
