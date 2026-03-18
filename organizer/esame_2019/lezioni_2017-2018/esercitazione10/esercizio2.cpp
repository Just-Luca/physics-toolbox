#include <iostream>
#include <fstream>
#include <vector>

#include <TCanvas.h>
#include <TApplication.h>
#include <TStyle.h>
#include <TH1.h>
#include <TF1.h>
#include <cmath>

#include "MyFunz.h"

int main(int argc, char** argv)
{
	TApplication *myApp = new TApplication("app", 0, 0);
	
	std::ifstream myFile("momenta.txt"); 
	if (myFile.good()==false)
	{
		std::cout << "Errore apertura file" << std::endl;
		return -1;
	}
	
	double num;
	std::vector<double> ListNum;
	int Ndata=0;
	
	while (myFile.eof()==false)
    {
    	myFile >> num;
      	ListNum.push_back(num);
      	Ndata++; 
	}
	
	TCanvas* MyCanv = new TCanvas("MyCanv","MyCanv",0,0,700,500);
	TH1F *histo = new TH1F ("histo","distribuzione dei dati", 200, 0, 4.5);
	for (int i=0; i<Ndata; i++)
		histo->Fill(ListNum[i]);

	histo->Draw();
	
	histo->SetFillColor(kYellow);
	histo->GetXaxis() -> SetTitle("variabile x");
	histo->GetYaxis() -> SetTitle("conteggi");
	
	
	gStyle -> SetOptFit(1111);
	int nPar = 2;
	
	//Fitto la prima funzione
	TF1* MyFun1 = new TF1("myFun1", dist1, 0, 4.5, nPar);
	MyFun1->SetParameter(0, 1);	
	MyFun1->SetParameter(1, 1);

	
	//fitto la seconda funzione
	TF1* MyFun2 = new TF1("MyFun2", dist2, 0, 4.5, nPar);
	MyFun2->SetParameter(0, 1);
	MyFun2->SetParameter(1, 1);

	//fitto la terza funzione
	TF1* MyFun3 = new TF1("MyFun3", dist3, 0, 4.5 , nPar);
	MyFun3->SetParameter(0, 1);
	MyFun3->SetParameter(1, 1);
	
	histo->Draw();

	histo->Fit("MyFun1", "+");
	MyFun2->SetLineColor(kGreen);
	histo->Fit("MyFun2","+");
	MyFun3->SetLineColor(kBlue);
	histo->Fit("MyFun3","+");

	MyCanv->Modified();
	MyCanv->Update();
	
	
	myApp->Run();
	
	return 0;
}
