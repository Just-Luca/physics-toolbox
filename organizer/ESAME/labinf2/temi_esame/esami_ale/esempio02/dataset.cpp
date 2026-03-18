#include "dataset.h"
#include <iostream>

#include <TH1D.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TApplication.h>
#include <TStyle.h>

#include <TMath.h>

/*
STRINGA PER COMPILARE:
 c++ -o dataset dataset.cpp `root-config --cflags --glibs` dataset.cc
 */


using namespace std;

int main (int argc, char** argv){

  //istanzio i due oggetti dataset con il construttore che li inizializza con i
  //due file da leggere 
  dataset datasetA(argv[1]);
  dataset datasetB(argv[2]);

  //Istanzio la TApplication per visualizzare gli istogrammi, il TCAnvas, e gli
  //istogrammi
  gStyle -> SetOptFit(1112); //codice per visualizzare tutti i parametri
  TApplication* TApp   = new TApplication ("TApp", NULL, NULL);
  TCanvas* 	Canv   = new TCanvas ("CanvA", "distribuzioni", 0,0,700,500);
  TH1D* 	HistoA = new TH1D ("HistoA", "disribuzione A", 22, 0,22);
  TH1D* 	HistoB = new TH1D ("HistoB", "disribuzione B", 22, 0,22);

  //utilizzo due cicli for e il metodo Fill per riempire gli istogrammi
  for (int i = 0; i< datasetA.GetNdati(); i++){
    HistoA -> Fill(datasetA.GetDato(i));
  }

  for (int i = 0; i< datasetA.GetNdati(); i++){
    HistoB -> Fill(datasetB.GetDato(i));
  }
  //definisco due funzioni TF1 di tipo gaussiano per fittare gli istogrammi
  TF1* gaus1 = new TF1 ("gaus1", "gaus", 0, 22);
  TF1* gaus2 = new TF1 ("gaus2", "gaus", 0, 22);
  gaus1 -> SetLineColor (kBlue);
  gaus2 -> SetLineColor (kRed);

  //fitto gli istogrammi
  HistoA -> Fit("gaus1");
  HistoB -> Fit("gaus2");
  cout << "---------------------------------------------------------------------"
       << endl;
  //stampo a schermo i risultati del fit per datasetA
  cout << "DATASET A:" 	     << endl
       << "chi^2 = " 	     << gaus1 -> GetChisquare()  << endl
       << "NDF = " 	     << gaus1 -> GetNDF() << endl
       << "Reduced chi^2 = " << gaus1 -> GetChisquare() / gaus1 -> GetNDF()
    			     << endl
       << "p-value = " 	     << gaus1 -> GetProb()
       << endl;
  //stabilisco se il fit e` buono entro un intevallo di confidenza del 95%
  if (gaus1 -> GetProb() > 0.05){
    cout << "buon adattamento alla distribuzione ipotizzata con un intervallo "
	 << endl
	 << "di confidenza del 95%"<< endl << endl;
  } else {
    cout << "adattamento non buono con un intervallo di confidenza del 95%"
	 << endl << endl;
  }
  //stampo a schermo il valore della miglior stima di X per il set A
  cout << "X = "   << datasetA.GetMedia() << endl
       << "err = " << datasetA.GetDevstd()/sqrt(datasetA.GetNdati()) << endl;
  cout << "--------------------------------------------------------------------"
       <<endl;

  //ripeto la stessa cosa per il set B
  cout << "DATASET B:" 	     << endl
       << "chi^2 = " 	     << gaus2 -> GetChisquare()  << endl
       << "NDF = " 	     << gaus2 -> GetNDF() << endl
       << "Reduced chi^2 = " << gaus2 -> GetChisquare() / gaus1 -> GetNDF()
       			     << endl
       << "p-value = " 	     << gaus2 -> GetProb()
       << endl;
  if (gaus2 -> GetProb() > 0.05){
    cout << "buon adattamento alla distribuzione ipotizzata con un intervallo "
	 << endl
	 << "di confidenza del 95%"<< endl << endl;
  } else {
    cout << "adattamento non buono con un intervallo di confidenza del 95%"
	 << endl << endl;
  }
  cout << "X = "   << datasetB.GetMedia() << endl
       << "err = " << datasetB.GetDevstd()/sqrt(datasetB.GetNdati()) << endl;
  cout << "--------------------------------------------------------------------"
       <<endl;
  
  //Stabilisco se le due misure sono compatibili (nell'ipotesi garantita dal
  //testo che il numero di misure sia sufficientemente grande) con un intervallo
  //di confidenza del 95%
  double mean1, mean2, err1, err2, t, prob;

  mean1 = datasetA.GetMedia();
  mean2 = datasetB.GetMedia(); 
  err1  = datasetA.GetDevstd()/sqrt(datasetA.GetNdati());
  err2  = datasetB.GetDevstd()/sqrt(datasetB.GetNdati());

  t = fabs(mean1-mean2) / sqrt(err1*err1 + err2*err2);
  prob = TMath::Erfc(t/sqrt(2));

  //stampo a schermo i risultati
  cout << "COMPATIBILITA` TRA LE MISURE:" <<endl
       << "prob = " << prob << endl;
  if (prob > 0.05) {
    cout << "le misure sono compatibili in un intervallo di confidenza del 95%"
	 << endl;
  } else {
    cout << "le misure non  sono compatibili in un intervallo di confidenza " 
	 << endl
	 << "del 95%"
	 << endl;
  }  
   
  //mi sposto nel canvas per disegnare gli istogrammi (entrambi sullo stesso
  //canvas)
  Canv   ->cd();

  HistoA -> SetLineColor (kBlue);
  HistoB -> SetLineColor (kRed);

  HistoA -> Draw();
  HistoB -> Draw("same");

  Canv   -> Modified();
  Canv   -> Update();

  TApp -> Run();
}
