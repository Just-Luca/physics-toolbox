#include "dataset.h"

#include <fstream>
#include <iostream>

#include <cmath>

using namespace std;

dataset::~dataset(){}

dataset::dataset (){
  N_p  = 0;
  mu_p = 0;
  dati_p.clear();
  media_p = 0;
  devstd_p = 0;
}

dataset::dataset (const char* nomefile){
  //inizializzo a 0 tutte le variabili private
  N_p  = 0;
  mu_p = 0;
  dati_p.clear();
  media_p = 0;
  devstd_p = 0;

  //apro il file e controllo che l'operazione avvenga con successo,
  //in caso contrario stampo a schermo un messaggio di errore.
  //Dichiaro una variabile che serve per estrarre i dati dal file in lettura.

  int x;
  
  ifstream infile (nomefile);
  if (! infile.good()){
    cout << "ERRORE: impossibile aprire il file " << nomefile << endl;
  }
  else {
    while (true){ //imposto un ciclo per leggere il file fino a EOF
      infile >> x;
      if (infile.eof()) break;
      dati_p.push_back(x); //inserisco di volta in volta il dato nel vettore
      N_p ++; //conto le entrate
      mu_p += x;
      //sommo di volta in volta l'entrata alla variabile mu_p che mi servira` per
      //calcolare la media
    }
    //calcolo la media del campione dividendo al somma mu_p per il numero di
    //entrate
    mu_p    = mu_p/N_p;
    //calcolo la deviazione standard del campione.
    for (int i=0; i<N_p; i++){
      devstd_p += (dati_p[i]-mu_p)*(dati_p[i]-mu_p);
    }
    devstd_p = devstd_p / (N_p-1);
    devstd_p = sqrt(devstd_p);
  }
}
//implemento i metodi che restituiscano i valori delle variabili private
double dataset::GetMedia(){
  return mu_p;
}
double dataset::GetDevstd(){
  return devstd_p;
}
int dataset::GetNdati (){
  return N_p;
}

int dataset::GetDato(const int& i){
  return dati_p[i];
}
