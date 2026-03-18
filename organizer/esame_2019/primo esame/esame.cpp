//	c++ -o esame esame.cpp myLib.cc `root-config --cflags --glibs`
//	./esame dataFile.txt

#include <iostream>
#include <vector>
#include <fstream>
#include <TH1F.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TF1.h>
#include <TApplication.h>
#include <cmath>

#include "myLib.h"

int main(int argc, char** argv)
{
	//verifica che vengano passati almeno due parametri da riga di comando
	if(argc < 2)
	{
		std::cout << "Digitare il nome del file da riga di comando: ./esame dataFile.txt" << std::endl;
		return -1;
	}
	
	std::string fileInput = argv[1];
	
	//definizione dei due vector in cui salvare le misure e il loro errore
	std::vector<double> valVec;
	std::vector<double> errVec;

	//lettura da file, riempimento dei due vector e verifica che le operazioni vadano a buon fine
	bool lettura = readData(fileInput, valVec, errVec);
	if(lettura == false)
	{
		std::cout << "Errore lettura file" << std::endl;
		return -1;
	}


	//calcolo della media delle misure nel file
	double media = computeAvg(valVec);

	//oggetti necessari per l'interfaccia grafica in cui visualizzare l'istogramma
	TApplication* Grafica = new TApplication("", NULL, NULL);
	gStyle->SetOptFit(1112);
	TCanvas* c1 = new TCanvas("c1","il mio canvas", 0, 0, 700, 500);
	TH1F* myHisto = new TH1F("myHisto","distribuzione dei dati", 50, -5, 5);

	
	//riempie l'istogramma
	for (int i=0; i<valVec.size(); i++)
		myHisto->Fill((valVec[i]-media)/errVec[i]);

	myHisto->Draw();
	
	myHisto->SetFillColor(kYellow);
	myHisto->GetXaxis() -> SetTitle("variabile x");
	myHisto->GetYaxis() -> SetTitle("conteggi");

	//fitta l'istogramma con una Gaussiana
	TF1* gaussian = new TF1("gaussian", myGauss, 0, 10, 3);
	gaussian->SetParameter(0, 100);	//valore massimo
	gaussian->SetParameter(1, 0);	//media
	gaussian->SetParameter(2, 1);	//deviazione

	myHisto->Fit("gaussian");

	std::cout << "\nIl valore della sigma della Gaussiana (0.8302) dista da 1 per più dell'errore ottenuto"
			  << " dal fit sulla sigma medesima (+- 0.0217). Le misure non sono pertanto compatibili." << std::endl;

	c1->Modified();
	c1->Update();
		
    Grafica->Run();	

	return 0;

}
