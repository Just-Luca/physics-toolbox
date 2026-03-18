#include <iostream>
#include <cstdlib>
#include <TCanvas.h>
#include <TH1D.h>
#include <TApplication.h>
#include <TStyle.h>
#include <TF1.h>
#include <cmath>
#include <vector>
#include <string>
#include <fstream>


int main(int argc, char** argv)
{
	//verifica che vengano passati almeno due parametri da riga di comando
	if(argc < 2)
	{
		std::cout << "Digitare il nome del file da riga di comando!: ./esame ten_s.txt" << std::endl;
		return -1;
	}
	
	std::string fileInput = argv[1];
	std::ifstream InFile (fileInput.c_str());
	
	//verifica che l'apertura e la lettura del file vadano a buon fine
	if (InFile.good() == 0)
    {
    	std::cout << "Errore! Non è possibile aprire il file "<< fileInput <<std::endl;
    	return -1;
    }
    
    // definisco due vector per memorizzare i numeri contenuti nel file
    std::vector<double> vec1; 
	std::vector<double> vec2;
  
	double x=0;
	double y=0;
	int Nrighe=0;
  
	while (true)	// imposto un loop infinito, che verrà interrotto con l'istruzione break
    {
    	InFile >> x >> y;
    	if (InFile.eof()==true) // il metodo eof() restituisce true alla fine del file
			break;
      	vec1.push_back(x); 
      	vec2.push_back(y);
      	Nrighe++;
    }
	InFile.close();
	
	int Nbins = 20;
	int a = -0.5;
	int b = 19.5;
	
	//instanzio gli oggetti per creare l'interfaccia grafica per mostrare gli istogrammi
	gStyle -> SetOptFit(1112);
	TApplication* myApp = new TApplication ("myApp", NULL, NULL);
	TCanvas* myCanv1 = new TCanvas ("myCanv1", "distribuzione uniforme", 0, 0, 700, 500);
  
	//definisce un istogramma di 20 bin nell'intervallo [-0.5, 19.5] e lo riempie con le misure di Luigi
	TH1D* myHisto_Luigi = new TH1D("myHisto_Luigi", "distribuzione normale", Nbins, a, b);
	for(int i=0; i<vec1.size(); i++)
		myHisto_Luigi->Fill(vec1[i]);
  	
  	//definisce un istogramma di 20 bin nell'intervallo [-0.5, 19.5] e lo riempie con le misure di Luisa
	TCanvas* myCanv2  = new TCanvas ("myCanv2", "distribuzione normale", 0, 0, 700, 500);
	TH1D* myHisto_Luisa = new TH1D("myHisto_Luisa", "distribuzione normale", Nbins, a, b);
	for(int i=0; i<vec2.size(); i++)
		myHisto_Luisa->Fill(vec2[i]);
  	
  	//calcolo media, deviazione standard ed errore sulla media di Luigi
  	double somma1 = 0, somma_quadrati1 = 0;
  	double media1, devstd1, errmedia1;
  	
  	for (int i=0; i<vec1.size(); i++)
    {
	    somma1 += vec1[i];
	    somma_quadrati1 += vec1[i]*vec1[i];
    }
	media1 = somma1/(float)Nrighe;
	devstd1 = sqrt(fabs(somma_quadrati1/(float)Nrighe - media1*media1));	
	errmedia1 = devstd1/(sqrt(Nrighe));

	std::cout << "\nDati di Luigi:" << std::endl;
	std::cout << "Media = " << media1 << std::endl;
	std::cout << "Dev.Std = " << devstd1 << std::endl;
	std::cout << "Errore sulla media = " << errmedia1 << std::endl;
	
	//calcolo media, deviazione standard ed errore sulla media di Luisa
  	double somma2 = 0, somma_quadrati2 = 0;
  	double media2, devstd2, errmedia2;
  	
  	for (int i=0; i<vec2.size(); i++)
    {
	    somma2 += vec2[i];
	    somma_quadrati2 += vec2[i]*vec2[i];
    }
	media2 = somma2/(float)Nrighe;
	devstd2 = sqrt(fabs(somma_quadrati2/(float)Nrighe - media2*media2));	
	errmedia2 = devstd2/(sqrt(Nrighe));

	std::cout << "\nDati di Luisa:" << std::endl;
	std::cout << "Media = " << media2 << std::endl;
	std::cout << "Dev.Std = " << devstd2 << std::endl;
	std::cout << "Errore sulla media = " << errmedia2 << std::endl;
   
	myCanv1 -> cd();
	myHisto_Luigi -> Draw ();
	myCanv1 -> Modified();
	myCanv1 -> Update();
	
	myCanv2 -> cd();
	myHisto_Luisa -> Draw ();
	myCanv2 -> Modified();
	myCanv2 -> Update();

	myApp -> Run();	
	return 0;
	return 0;
}
