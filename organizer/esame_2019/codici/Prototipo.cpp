#include <iostream>
#include <cmath>

#include <TStyle.h>
#include <TApplication.h>
#include <TCanvas.h>
#include <TF1.h>
#include <TGraphErrors.h>
#include <TAxis.h>
#include <TFitResult.h>
#include <TMatrixDSym.h>

/* FDD sta per funzione da definire
   andrà sostituito insieme a min, max, parametri (questi per la TF1), */

using namespace std;

double FDD(double* x, double* par){
	double val = ?????;
	return val;
}


void ComputeChi2(TGraphErrors* myData, TF1* myFun, double& chi2, double& NDF)
{
  double result = 0;

  for (int i = 0; i < myData->GetN(); i++)
    {
      result += pow(myData->GetY()[i] - myFun->Eval(myData->GetX()[i]),2.) /
	(pow(myData->GetErrorY(i),2.) + pow(myFun->Derivative(myData->GetX()[i])*myData->GetErrorX(i),2.));
    }
  
  chi2 = result;
  NDF  = myData->GetN() - myFun->GetNpar();
}


int main(int argc, char** argv)
{
  if (argc < 2)
    {
      cout << "Errore Argc: inserire file txt corretto" << endl;
      return 1;
    }
  
	gStyle->SetOptFit(1112);
	TApplication* myApp = new TApplication("myApp", NULL, NULL);
 	TCanvas* myC = new TCanvas("myC","myC",0,0,700,500);
	
	TGraphErrors* myGraph = new TGraphErrors(argv[1]);
	myGraph->SetMarkerStyle(20);
  	myGraph->SetMarkerSize(0.2);
	myGraph->GetXaxis()->SetTitle("Titolo x");
  	myGraph->GetYaxis()->SetTitle("Titolo y");

	TF1* myFun = new TF1("myFun",FDD,min,max,parametri);
  	myFun->SetParameter(0,0);
  	myFun->SetParameter(1,0);
 	myFun->SetParName(0,"Par0");
  	myFun->SetParName(1,"Par1");


  	myC->cd();
  	myGraph->Draw("AP");
  	myGraph->Fit("myFun");	
 	myC->Modified();
 	myC->Update();


	std::cout << "Reduced Chi-2: ";
  	std::cout << myFun->GetChisquare()/myFun->GetNDF() << std::endl;
  	std::cout << "p-value: " << myFun->GetProb() << std::endl;

  	double chi2, NDF;
  	ComputeChi2(myGraph,myFun,chi2,NDF);
  	std::cout << "My Chi-2: " << chi2 << std::endl;
  	std::cout << "My NDF: " << NDF << std::endl;

  	myC->Print("V");

  	myApp->Run();
  	return 0;
}
