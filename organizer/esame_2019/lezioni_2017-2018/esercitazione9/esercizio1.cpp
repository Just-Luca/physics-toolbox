#include <iostream>
#include <fstream>

#include <TCanvas.h>
#include <TApplication.h>
#include <TStyle.h>
#include <TH1D.h>
#include <TF1.h>
#include <cmath>

double myParabola(double* x, double* par)
{
	return par[0]*x[0]*x[0] + par[1]*x[0] + par[2];
}

double myGauss(double* x, double* par)
{
	return par[0]*exp(-0.5*(pow((x[0]-par[1])/ par[2], 2)));
}

double gauss_parabola(double* x, double* par)
{
	//double var = par[0]*exp(-0.5*(pow((x[0]-par[1])/ par[2], 2)));
	//var += par[3]*x[0]*x[0] + par[4]*x[0] + par[5];

	double var = myGauss(x, par) + myParabola(x, par+3);
	return var;
}

bool ReadData(char* fileName, TH1D* myHisto)
{
	std::ifstream myFile(fileName);
	std::vector<double> vec1;
	
	if (myFile.good() == 0)
    {
    	std::cout << "Errore! Non è possibile aprire il file " << fileName <<std::endl;
    	return false;
    }
    
    double x = 0;
    while (myFile.eof()==false)
    {
    	myFile >> x;
      	vec1.push_back(x);
    }
	myFile.close();
	
	for(int i=0; i<vec1.size(); i++)
		(*myHisto).Fill(vec1[i]); //oppure myHisto->Fill(vec1[i])
	
	return true;
}

void computeChi2(TH1D* myHisto, TF1* myFun, double& chi2, double& NDF)
{
	double chi_quadro = 0;
	for(int i=1; i <= (myHisto->GetNbinsX()); i++)
		chi_quadro += pow((myHisto->GetBinContent(i) - myFun->Eval(myHisto->GetBinCenter(i))),2.) / myHisto->GetBinContent(i);
		
  	chi2 = chi_quadro;
	NDF  = myHisto->GetNbinsX() - myFun->GetNpar();
}

/************************************************************************************************************************/

int main(int argc, char** argv)
{
	int nBins = 100;
	int xMin = 0;
	int xMax = 10;
	
	//verifico che venga passato almeno un parametro da riga di comando
	if(argc < 2)
	{
		std::cout << "Digitare il nome del file da riga di comando: ./esercizio1 data1.txt" << std::endl;
		return 1;
	}

	TApplication* myApp = new TApplication("myApp", NULL, NULL);  
	TCanvas* myCanv = new TCanvas("myCanv","myCanv",0,0,700,500);
	TH1D* myHisto = new TH1D("myHisto", "myHisto", nBins, xMin, xMax);

	if (ReadData(argv[1],myHisto) == false)
    {
      std::cout << "Error reading data file" << std::endl;
      return -1;
    }

	TF1* myFun = new TF1("myFun", gauss_parabola, 0, 10, 6);
	myFun->SetParameter(0, 4000);
	myFun->SetParameter(1, 5);
	myFun->SetParameter(2, 1);
	
	myFun->SetParameter(3, -40);
	myFun->SetParameter(4, 400);
	myFun->SetParameter(5, 8000);
	
	
	myCanv->cd();
	myHisto->Draw();
	myHisto->Fit("myFun");
  
	myCanv->Modified();
	myCanv->Update();

	std::cout << "Reduced Chi-2: ";
	std::cout << myFun->GetChisquare()/myFun->GetNDF() << std::endl;
	std::cout << "p-value: " << myFun->GetProb() << std::endl;
	
	double chi2, NDF;
	computeChi2(myHisto, myFun, chi2, NDF);
	std::cout << "My Chi-2: " << chi2 << std::endl;
  	std::cout << "My NDF: " << NDF << std::endl;
	
	myApp->Run();
	
	return 0;
}
