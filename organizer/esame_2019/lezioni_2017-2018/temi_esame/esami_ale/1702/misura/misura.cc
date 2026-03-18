#include "misura.h"

#include <fstream>
#include <iostream>

#include <cstdlib>
#include <cmath>

#include <TMath.h>

using namespace std;

//definisco il default constructor

misura::misura () {
  cout << "Inserire la misura: ";
  cin >> X_p;
  cout << "Inserire l'errore : ";
  cin >> EX_p;
}

//definisco il costructor che prende diversi dati da file e calcola la stima per
//X e EX.
misura::misura(const string& filename){
  //dichiaro un vettore di double per salvare i dati estratti, una variabile
  //double per estrarre il sigolo dato dal file e una variabile int N per contare
  //le entrate.
  vector <double> data;
  double x;
  int N = 0;

  //inizializzo a 0 le variabili private della classe.
  X_p = 0; EX_p  = 0;

  //leggo il file e calcolo la stima per X, che e` la media campionaria
  ifstream infile (filename.c_str());
  if (! infile.good()){
    cout << "ERRORE: impossibile aprire il file " << filename << endl;
  } else {
    cout << "file aperto correttamente" << endl;
    while (true){ //imposto un ciclo per leggere il file fino a EOF
      infile >> x;
      if (infile.eof()) break;
      data.push_back(x); //inserisco di volta in volta il dato nell'istogramma
      N ++; //conto le entrate
      X_p += x;
      //uso la variabile privata per la stima della misura per calcolare la somma
      //delle entrate.
    }
    //calcolo la media campionaria (stima di X) dividendo la somma precedentemente
    //calcolata per il numero di entrate.
    X_p = X_p/N;
    //calcolo la stima dell'incertezza su X utilizzando l'estimatore unbiased.
    //l'incertezza sulla media, per il teorema del limite centrale, sara` la
    //deviazione standard della pdf del campione divisa per la radice quadrata
    //del numero di entrate che compongono il campione.

    for (int i=0; i<N; i++){
      EX_p += (data[i]-X_p)*(data[i]-X_p);
    }
    EX_p = EX_p / (N-1);
    EX_p = sqrt(EX_p);
    EX_p = EX_p / sqrt(N);
  }
}

//definisco il distruttore.
misura::~misura() {}

//definisco i metodi dichiarati nel file .h

void misura::Somma (const misura& other){
  double Xs, errXs;
  //la stima della somma e` la somma delle stime
  Xs = X_p + other.GetX();
  //l'incertezza e` la somma in quadratura delle incertezze.
  errXs = sqrt(EX_p*EX_p + other.GetEX()*other.GetEX());

  //stampo a schermo il risultato
  cout << "Somma = " << Xs << " +/- " << errXs << endl;
}

void misura::SommaCorr (const misura& other, const double &cov){}
void misura::Moltiplica (const misura& other){
  double X, errX;
  //la stima del prodotto e` il prodotto delle stime
  X = X_p * other.GetX();
  //l'incertezza e` la somma in quadratura delle incertezze.
  errX = sqrt(pow((other.GetX()*EX_p),2) + pow(X_p*other.GetEX(),2));
  //stampo a schermo il risultato
  cout << "Prodotto = " << X << " +/- " << errX << endl;
}

void misura::Confronta (const misura& other) const {
  double mean1, mean2, err1, err2, t, prob;

  mean1 = X_p;
  mean2 = other.GetX(); 
  err1  = EX_p;
  err2  = other.GetEX();
  
  t = fabs(mean1-mean2) / sqrt(err1*err1 + err2*err2);
  prob = TMath::Erfc(t/sqrt(2));

  //stampo a schermo i risultati
  cout << "prob = " << prob << endl;
  if (prob > 0.05) {
    cout << "le misure sono compatibili in un intervallo di confidenza del 95%"
	 << endl;
  } else {
    cout << "le misure non  sono compatibili in un intervallo di confidenza " 
	 << endl
	 << "del 95%"
	 << endl;
  }    
}
 
