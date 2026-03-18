#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>

#include <TApplication.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TF1.h>
#include <TStyle.h>
#include <TFitResult.h>
#include <TMatrixDSym.h>
#include <TGraphErrors.h>
#include <TAxis.h>

using namespace std;

double funzione (double* x, double* par) {

	double val = par[0]*pow(x[0],2) + par[1]*x[0] + par[2]; 
	return val;
}

/*void ComputeChi2(TGraphErrors* myData, TF1* myFun, double& chi2, double& NDF) {
	
	double result = 0;

	for (int i = 0; i < myData->GetN(); i++) {
	
      	result += pow(myData->GetY()[i] - myFun->Eval(myData->GetX()[i]),2.) /
(pow(myFun->Derivative(myData->GetX()[i])*myData->GetErrorX(i),2.));
	}
  
	chi2 = result;
	NDF  = myData->GetN() - myFun->GetNpar();
}*/

int main(int argc, char** argv) {

	ifstream in (argv[1]); 
	if (in.good()==false) {
		cout << "Errore apertura file" << endl;
		return 1;
	}
	
	double num, min, max;
	vector<double> ListNum;
	int Ndata=0;
	while (true) {
	
		in>>num;
		if (in.eof()==true) break;
		ListNum.push_back(num);
		if (Ndata == 0) {
			min=num;
			max=num;
		}
		else {
			if (num<min) min=num;
			if (num>max) max=num;
		}
				
		Ndata++; 
	}
  
	gStyle->SetOptFit(1112);
	TApplication* myApp = new TApplication("myApp", NULL, NULL);
	TCanvas* myC = new TCanvas("myC","myC",0,0,700,500);
	
	TGraphErrors* myGraph = new TGraphErrors(argv[1]);
	myGraph->SetMarkerStyle(20);
	myGraph->SetMarkerSize(0.2);
	myGraph->GetXaxis()->SetTitle("Titolo x");
	myGraph->GetYaxis()->SetTitle("Titolo y");

	TF1* myFun = new TF1("myFun", funzione, min, max, 3);
	myFun->SetParameter(0, 1);
	myFun->SetParameter(1, 1);
	myFun->SetParameter(2, 1);
	
	myFun->SetParName(0, "a");
	myFun->SetParName(1, "b");
	myFun->SetParName(2, "c");

	myC->cd();
	myGraph->Draw("AP");
 	myGraph->Fit("myFun");	
	myC->Modified();
	myC->Update();

	/*std::cout << "Reduced Chi-2: ";
	std::cout << myFun->GetChisquare()/myFun->GetNDF() << std::endl;
	std::cout << "p-value: " << myFun->GetProb() << std::endl;

	double chi2, NDF;
	ComputeChi2(myGraph,myFun,chi2,NDF);
	std::cout << "My Chi-2: " << chi2 << std::endl;
	std::cout << "My NDF: " << NDF << std::endl;
	*/
	
	myC->Print("V");

	myApp->Run();
  	
 	return 0;
}
