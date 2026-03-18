#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>
#include <TCanvas.h>
#include <TH1.h>
#include <TApplication.h>
#include <TStyle.h>
#include <TF1.h>

#include "myLib.h"

int main(int argc, char** argv)
{
	std::vector<double> vectNumX;
	std::vector<double> vectNumY;
	std::vector<double> vectNumRapporto;
	//lettura da file, riempimento dei due vector e verifica che le operazioni vadano a buon fine
	bool lettura = readData("correlated.txt", vectNumX, vectNumY, vectNumRapporto);
	if(lettura == false)
	{
		std::cout << "Errore lettura file" << std::endl;
		return -1;
	}
	
	/***********************************************************************************************/
	
	//calcolo media e deviazione standard delle misure X
	double sommaX = 0, somma_quadratiX = 0;
  	double mediaX, devstdX, errmediaX;
  	
  	for (int i=0; i<vectNumX.size(); i++)
    {
	    sommaX += vectNumX[i];
	    somma_quadratiX += vectNumX[i]*vectNumX[i];
    }
	mediaX = sommaX/(float)vectNumX.size();
	devstdX = sqrt(fabs(somma_quadratiX/(float)vectNumX.size() - mediaX*mediaX));	
	errmediaX = devstdX/(sqrt(vectNumX.size()));

	std::cout << "\nDati X:" << std::endl;
	std::cout << "Media = " << mediaX << std::endl;
	std::cout << "Dev.Std = " << devstdX << std::endl;
	std::cout << "Errore sulla media = " << errmediaX << std::endl;
	
	//calcolo media e deviazione standard delle misure Y
	double sommaY = 0, somma_quadratiY = 0;
  	double mediaY, devstdY, errmediaY;
  	
  	for (int i=0; i<vectNumY.size(); i++)
    {
	    sommaY += vectNumY[i];
	    somma_quadratiY += vectNumY[i]*vectNumY[i];
    }
	mediaY = sommaY/(float)vectNumY.size();
	devstdY = sqrt(fabs(somma_quadratiY/(float)vectNumY.size() - mediaY*mediaY));	
	errmediaY = devstdY/(sqrt(vectNumY.size()));

	std::cout << "\nDati Y:" << std::endl;
	std::cout << "Media = " << mediaY << std::endl;
	std::cout << "Dev.Std = " << devstdY << std::endl;
	std::cout << "Errore sulla media = " << errmediaY << std::endl;
	
	//calcolo media e deviazione standard delle misure X/Y
	double sRapporto = 0, sqRapporto = 0;
  	double mRapporto, dsRapporto, emRapporto;
  	
  	for (int i=0; i<vectNumRapporto.size(); i++)
    {
	    sRapporto += vectNumRapporto[i];
	    sqRapporto += vectNumRapporto[i]*vectNumRapporto[i];
    }
	mRapporto = sRapporto/(float)vectNumRapporto.size();
	dsRapporto = sqrt(fabs(sqRapporto/(float)vectNumRapporto.size() - mRapporto*mRapporto));	
	emRapporto = dsRapporto/(sqrt(vectNumRapporto.size()));

	std::cout << "\nDati Rapporto:" << std::endl;
	std::cout << "Media = " << mRapporto << std::endl;
	std::cout << "Dev.Std = " << dsRapporto << std::endl;
	std::cout << "Errore sulla media = " << emRapporto << std::endl;

	/*************************************************************************************************************/
	
	//oggetti per l'interfaccia grafica per mostrare gli istogrammi
	gStyle -> SetOptFit(1112);
	TApplication* myApp = new TApplication ("myApp", NULL, NULL);
	TCanvas* myCanv1 = new TCanvas ("myCanv1", "distribuzione uniforme", 0, 0, 700, 500);
  
	//definisce un istogramma di 1000 bin e lo riempie con le misure X
	TH1F* myHisto_X = new TH1F("myHisto_X", "distribuzione normale", 1000, 650, 950);
	for(int i=0; i<vectNumX.size(); i++)
		myHisto_X->Fill(vectNumX[i]);
  	
  	//definisce un istogramma di 1000 bin e lo riempie con le misure Y
	TCanvas* myCanv2  = new TCanvas ("myCanv2", "distribuzione normale", 0, 0, 700, 500);
	TH1F* myHisto_Y = new TH1F("myHisto_Y", "distribuzione normale", 1000, 200,600);
	for(int i=0; i<vectNumY.size(); i++)
		myHisto_Y->Fill(vectNumY[i]);
	
	//definisce un istogramma di 1000 bin e lo riempie con le misure X/Y
	TCanvas* myCanv3  = new TCanvas ("myCanv3", "distribuzione normale", 0, 0, 700, 500);
	TH1F* myHisto_Rapporto = new TH1F("myHisto_Rapporto", "distribuzione normale", 1000, 0.5, 3.5);
	for(int i=0; i<vectNumRapporto.size(); i++)
		myHisto_Rapporto->Fill(vectNumRapporto[i]);
	
	myCanv1 -> cd();
	myHisto_X -> Draw ();
	myCanv1 -> Modified();
	myCanv1 -> Update();
	myHisto_X->Fit("gaus");
	
	myCanv2 -> cd();
	myHisto_Y -> Draw ();
	myCanv2 -> Modified();
	myCanv2 -> Update();
	myHisto_Y->Fit("gaus");

	myCanv3 -> cd();
	myHisto_Rapporto -> Draw ();
	myCanv3 -> Modified();
	myCanv3 -> Update();
	myHisto_Rapporto->Fit("gaus");
	
	myApp -> Run();	
	return 0;
}
