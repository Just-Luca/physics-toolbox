#include <fstream>
#include <iostream>
#include <ctime>
#include <TH1I.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TApplication.h> 
#include "TF1.h"
#include <cmath>
#include "dataset.h"



//c++  dataset.cpp  dataset.cc `root-config --cflags --glibs` -o dataset


using namespace std;


int main(int argv, char ** argc) {	
	
	TApplication* Grafica= new TApplication("", NULL, NULL);
	gStyle->SetOptFit(1111);
	TCanvas* c1=new TCanvas("c1","il mio canvas");

    dataset A("datiA.txt");
    dataset B("datiB.txt");
    
    cout << "Media A : " << A.GetMedia() << endl;
    cout << "Dev. std. A : " << A.GetDevstd() << endl;
    double devstdmA = A.GetDevstd()/sqrt((double)A.GetNdati());
    cout << "Dev. std. mean A : " << devstdmA << endl;
    cout << "Media B : " << B.GetMedia() << endl;
    cout << "Dev. std. B : " << B.GetDevstd() << endl;
    double devstdmB = B.GetDevstd()/sqrt((double)B.GetNdati());
    cout << "Dev. std. mean B : " << devstdmB << endl;

    int min=0;
    int max = (int) 10*A.GetDevstd();
    int nbin = max;
    TH1I *histoA = new TH1I("hd","Istogrammi di A (verde) e B (rosso) ",nbin,min,max);
    TH1I *histoB = new TH1I("hd","il mio istogramma B",nbin,min,max);
	
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
    cout << "Chi2 A : " << fA->GetChisquare() << endl;
    cout << "nDOF A : " << fA->GetNDF() << endl;
    cout << "Chi2 B : " << fB->GetChisquare() << endl;
    cout << "nDOF B : " << fB->GetNDF() << endl;
    cout << "Chi2/nDOF A : " << fA->GetChisquare()/fA->GetNDF() << endl;
    cout << "Chi2/nDOF B : " << fB->GetChisquare()/fB->GetNDF() << endl;
    
    double devstdm = sqrt(devstdmA*devstdmA + devstdmB*devstdmB);
   
    double t = (A.GetMedia() - B.GetMedia())/devstdm;
    //nell'approssimazione N sufficientemente grande, la R.V. t è distribuita come una Gauss(mu=0,sigma=1)
    //l'intervallo che corrisponde al 95\% di probabilià è [-1.96, 1.96] 
    
    cout << "\nTest di t = " << t << endl;
    
    if(fabs(t) > 1.96){
        cout << "B non compatibile con A entro il 5%" << endl;
    } else {
        cout << "B compatibile con A entro il 5%" << endl;
    }
    c1->Update();
    
    Grafica->Run("");
	return 0;
	}
	
	




