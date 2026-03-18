#include <iostream>
#include <fstream>
#include <iomanip>

#include <TCanvas.h>
#include <TApplication.h>
#include <TStyle.h>
#include <TH1.h>
#include <TF1.h>
#include <cmath>
#include <TFitResult.h>
#include <TMatrixDSym.h>

double fitfunc(double *x, double *p)
{
	double arg = (x[0]-p[1])/p[2];
	double gaus = p[0]*exp(-0.5*arg*arg);
	double parab = p[3] + p[4]*x[0] + p[5]*x[0]*x[0];
	return gaus + parab;
}

/******************************************************************************************************************************************/

int main(int argc, char** argv)
{
	TApplication *myApp = new TApplication("app", 0, 0);
	
	std::ifstream myFile(argv[1]); 
	if (myFile.good()==false)
	{
		std::cout << "Errore apertura file" << std::endl;
		return -1;
	}
	
	double num, min, max;
	std::vector<double> ListNum;
	int Ndata=0;
	
	while (myFile.eof()==false)
    {
    	myFile >> num;
      	ListNum.push_back(num);
      	
      	//trova massimo e minimo
		if (Ndata == 0)
		{
			min = num;
			max = num;
		}
		else
		{
			if(num < min)
				min = num;
			if(num > max)
				max = num;
		}		
		Ndata++; 
	}
	std::cout << "Il file " << argv[1] << " contiene " << Ndata << " dati" << std::endl;
	std::cout << "Minimo: " << min << std::endl;
	std::cout << "Massimo: " << max << std::endl;
	
	//disegna l'istogramma
	int NBin = 100;
	TH1F *h1 = new TH1F ("h1","distribuzione dei dati", NBin, min, max);
	for (int i=0; i<Ndata; i++)
		h1->Fill(ListNum[i]);
	
	TCanvas *c1 = new TCanvas();
	h1->Draw();
	
	h1->SetFillColor(kYellow);
	h1->GetXaxis() -> SetTitle("variabile x");
	h1->GetYaxis() -> SetTitle("conteggi");
	
	gStyle -> SetOptFit(1111);
	int nPar = 6;
	TF1 *f1 = new TF1("myFunz", fitfunc, min, max, nPar);
	f1->SetParameter(0, 10000);	//normalizzazione gaussiana (valore massimo)
	f1->SetParameter(1, 5.);	//valor medio della gaussiana
	f1->SetParameter(2, h1->GetRMS());	//varianza della gaussiana
	f1->SetParameter(3, 1000.);	//intercetta della parabola
	
	h1->Fit("myFunz");
	
	//parametri parabola
	double a = f1->GetParameter(5);
	double b = f1->GetParameter(4);
	double c = f1->GetParameter(3);
	std::cout << "Parametri della parabola: " << std::endl;
	std::cout << " a = " << a << " +- " << f1->GetParError(5) << std::endl;
	std::cout << " b = " << b << " +- " << f1->GetParError(4) << std::endl;
	std::cout << " c = " << c << " +- " << f1->GetParError(3) << std::endl;
	
	TF1 *f2 = new TF1 ("parabola","pol2", min, max);	
	f2->SetParameter(0, c);
	f2->SetParameter(1, b);
	f2->SetParameter(2, a);
	
	f2->SetLineColor(kBlue);
	f2->Draw("same");
	
	TFitResultPtr r = h1->Fit("myFunz", "S");
	r->Print("V");
	
	//matrice di covarianza
	TMatrixDSym cov = r->GetCovarianceMatrix();
	std::cout << "Matrice di covarianza " << std::endl;
	for (int i=0; i<nPar; i++)
	{
		for (int j=0; j<nPar; j++)
		{
			double sigma_ij = cov(i,j);
			std::cout << std::setw(15) << sigma_ij;
		}
		std::cout << std::endl;
	}
 
	f2->Draw("same");

	c1->Modified();
	c1->Update();
	
	myApp->Run();
	
	return 0;
}
