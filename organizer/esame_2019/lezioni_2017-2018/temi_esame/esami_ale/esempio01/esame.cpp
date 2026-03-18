#include <iostream>
#include <cstdlib>
#include "libreria.h"

#include <TH1D.h>
#include <TCanvas.h>
#include <TApplication.h>
#include <TStyle.h>

#define N 10000
#define NBins 100

using namespace std;

int main () {
  //inizializzo il seed del generatore di numeri pseudocasuali con il tempo
  //cosi' che a ogni esecuzione generi numeri diversi
  srand (time(NULL));

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
  //Individuo il minimo e il massimo valore di binContent[i] per definire il
  //range del nuovo isogramma.

  int min, max;
  MinMax (binContent, NBins, min, max);
  TCanvas* myCanv2  = new TCanvas ("myCanv2", "distribuzione uniforme", 0,0,
				   700, 500);
  
  TH1D*    myHisto2 = new TH1D ("myHisto2", "disribuzione bincontent", 20,
			    min , max );
  for (int i = 0; i<NBins; i++){
    myHisto2 -> Fill(binContent[i]);
  }  

  myCanv  -> cd();
  myHisto -> Draw ();
  myCanv  -> Modified();
  myCanv  -> Update();

  myCanv2  -> cd();
  myHisto2 -> Draw ();
  myHisto2 -> Fit ("gaus");
  myCanv2  -> Modified();
  myCanv2  -> Update();

  myApp   -> Run();
}
