#include <iostream>
#include <cstdlib>
#include "libreria.h"

#include <TH1D.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TApplication.h>
#include <TStyle.h>

#define N 10000
#define NBins 100

using namespace std;

int main () {
  //inizializzo il seed del generatore di numeri pseudocasuali con il tempo
  //cosi' che a ogni esecuzione generi numeri diversi
  //  srand (time(NULL));

  double data[N]; //vettore che contiene i numeri generati

  //riempio il vettore con numeri generati pseudocasualmente con una
  //distribuzione uniforme
  for (int i = 0; i < N; i++){
    data [i] = rand_range (0,1);
      }

  //instanzio gli oggetti per creare l'interfaccia grafica per mostrare
  //gli istogrammi
  gStyle -> SetOptFit(1112);
  TApplication* myApp   = new TApplication ("myApp", NULL, NULL);
  TCanvas* 	myCanv  = new TCanvas ("myCanv", "distribuzione uniforme", 0,0,
				      700, 500);
  //istanzio ora l'istogramma per rappresentare la distribuzione uniforme
  TH1D* 	myHisto = new TH1D ("myHisto", "disribuzione uniforme",
				    NBins, 0,1);
  //riempio l'istogramma
  for (int i = 0; i < N; i++){
    myHisto -> Fill (data[i]);
  }

  //recupero dall'istogramma il numero di dati contenuto in ciascun bin e salvo
  //i risultati in un vettore di double
  int binContent [NBins];
  cout << "CONTENUTO BIN:" << endl;
  for (int i = 0; i < NBins; i++){
    binContent [i] = myHisto -> GetBinContent (i+1);
    //(il conteggio dei bin parte da 1, non da zero)
    cout << "Bin n." << i+1 << " = " << binContent [i] << endl;
  }
  cout << "---------------------------------------------------------------------"
       << endl << endl;

  //bisogna inserire i dati ottenuti dall'ultimo ciclo for in un nuovo istogramma

  double min = N/NBins * 0.5;
  double max = N/NBins * 1.5;
  
  TCanvas* myCanv2  = new TCanvas ("myCanv2", "distribuzione uniforme", 0,0,
				   700, 500);
  
  TH1D*    myHisto2 = new TH1D ("myHisto2","disribuzione bincontent",20,min,max);
  for (int i = 0; i<NBins; i++){
    myHisto2 -> Fill(binContent[i]);
  }
  //definisco una funzione gaussiana per fittare l'istogramma
  TF1* gaussian = new TF1 ("gaussian", "gaus", min, max);
  //fitto l'istogramma
  myHisto2 -> Fit ("gaussian");

  //il numero k di conteggi in ciascun bin di un istogramma da una pdf è a sua
  //volta una variabile aleatoria la cui pdf è una binomiale. Nel limite in cui
  //si campiona un numero N sufficientemente grande di misure (e nel caso
  //presente tale ipotesi è verificata, essendo N = 10000), la variabile k è
  //distribuita secondo una gaussiana con media mu = Np dove p è la probabilità
  //che una misura cada in un bin, e varianza uguale alla media.
  //valuto la compatibilità tra i valori stimati e i valori attesi.

  //valori attesi di mu e sigma.
  double Emu       = N/NBins;
  double Esigma    = sqrt(Emu);
  double Omu       = gaussian -> GetParameter(1);
  double errOmu    = gaussian -> GetParError(1);
  double Osigma    = gaussian -> GetParameter(2);
  double errOsigma = gaussian -> GetParError(2);
  double pvalue1, pvalue2;

  if (testCompatibility(pvalue1, Omu, errOmu, Emu, 0.05)){
    cout << "il parametro mu e` compatibile con il valore atteso entro un"
	 << endl
	 << "intervallo di confidenza del 95%" << endl;
  } else {
    cout << "il parametro mu non e` compatibile con il valore atteso entro un"
	 << endl
	 << "intervallo di confidenza del 95%" << endl;
  }

  if (testCompatibility(pvalue2, Osigma, errOsigma, Esigma, 0.05)){
    cout << "il parametro sigma e` compatibile con il valore atteso entro un"
	 << endl
	 << "intervallo di confidenza del 95%" << endl;
  } else {
    cout << "il parametro sigma non e` compatibile con il valore atteso entro"
	 << endl
	 << "un intervallo di confidenza del 95%" << endl;
  }

  myCanv  -> cd();
  myHisto -> Draw ();
  myCanv  -> Modified();
  myCanv  -> Update();

  myCanv2  -> cd();
  myHisto2 -> Draw ();
  myCanv2  -> Modified();
  myCanv2  -> Update();

  myApp   -> Run();
}
