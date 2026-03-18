//		c++  -o esame esame.cpp  dataset.cpp `root-config --cflags --glibs`
//		./esame A.txt B.txt

#include <iostream>
#include <fstream>
#include <ctime>
#include <TH1I.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TApplication.h> 
#include "TF1.h"
#include <cmath>

#include "dataset.h"

int main(int argv, char ** argc)
{
	TApplication* Grafica = new TApplication("", NULL, NULL);
	gStyle->SetOptFit(1111);
	TCanvas* c1 = new TCanvas("c1", "il mio canvas");

    dataset A("A.txt");
    dataset B("B.txt");
    
    //calcolo media, deviazione standard ed errore sulla media
    std::cout << "Media A : " << A.GetMedia() << std::endl;
    std::cout << "Dev. std. A : " << A.GetDevstd() << std::endl;
    double DevStdMedia_A = A.GetDevstd()/sqrt((double)A.GetNdati());
    std::cout << "Dev. std. mean A : " << DevStdMedia_A << std::endl;
    
    std::cout << "Media B : " << B.GetMedia() << std::endl;
    std::cout << "Dev. std. B : " << B.GetDevstd() << std::endl;
    double DevStdMedia_B = B.GetDevstd()/sqrt((double)B.GetNdati());
    std::cout << "Dev. std. mean B : " << DevStdMedia_B << std::endl;
    
    
    int min=0;
    int max = (int) 10*A.GetDevstd();
    int nbin = max;
    TH1I* histoA = new TH1I("hd","Istogrammi di A (verde) e B (rosso) ", nbin, min, max);
    TH1I* histoB = new TH1I("hd","il mio istogramma B", nbin, min, max);
	
	int numero = 0;
	for (int i=0;i<A.GetNdati(); i++)
	{
		numero = A.GetDato(i);
		histoA->Fill(numero);
	}
    numero = 0;
    for (int i=0;i<B.GetNdati(); i++)
    {
        numero = B.GetDato(i);
        histoB->Fill(numero);
    }
    TF1 *fA = new TF1("fA", "gaus", min, max);
    TF1 *fB = new TF1("fB", "gaus", min, max);
    fA->SetLineColor(kGreen);
    fB->SetLineColor(kRed);
    histoA->Fit("fA");
    histoB->Fit("fB");
    histoA->SetLineColor(kGreen);
    histoB->SetLineColor(kRed);
	histoA->Draw();
    histoB->Draw("same");
    
    std::cout << "Chi2 A : " << fA->GetChisquare() << std::endl;
    std::cout << "nDOF A : " << fA->GetNDF() << std::endl;
    std::cout << "Chi2 B : " << fB->GetChisquare() << std::endl;
    std::cout << "nDOF B : " << fB->GetNDF() << std::endl;
    std::cout << "Chi2/nDOF A : " << fA->GetChisquare()/fA->GetNDF() << std::endl;
    std::cout << "Chi2/nDOF B : " << fB->GetChisquare()/fB->GetNDF() << std::endl;
    
    double devstdm = sqrt(DevStdMedia_A*DevStdMedia_A + DevStdMedia_B*DevStdMedia_B);
   
    double t = (A.GetMedia() - B.GetMedia())/devstdm;
    //nell'approssimazione N sufficientemente grande, la R.V. t è distribuita come una Gauss(mu=0,sigma=1)
    //l'intervallo che corrisponde al 95\% di probabilià è [-1.96, 1.96] 
    
    std::cout << "\nTest di t = " << t << std::endl;
    
    if(fabs(t) > 1.96)
        std::cout << "B non compatibile con A entro il 5%" << std::endl;
    else
        std::cout << "B compatibile con A entro il 5%" << std::endl;
   
    c1->Update();
    
    Grafica->Run("");
	return 0;
}

