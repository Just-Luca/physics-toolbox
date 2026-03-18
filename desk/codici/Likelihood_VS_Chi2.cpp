/*
c++ -o LikVSChi2 Likelihood_VS_Chi2.cpp `root-config --cflags --glibs`
*/

#include <iostream>
#include <fstream>

#include <TApplication.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TH1D.h>
#include <TF1.h>
#include <TFitResult.h>
#include <TMath.h>

using namespace std;


void chiquadro (TH1D* histo, double mean)
{
  int nbin = histo->GetNbinsX();
  double nbinpieni = 0;
  double chi1 = 0, chi2 = 0;

  for (int i = 1; i <= nbin; i++)
    {      
      if (histo->GetBinContent(i) > 0)
	{
	  chi1 += pow((histo->GetBinContent(i) - mean),2) / pow(histo->GetBinError(i),2);
	  chi2 += 2.*(mean - histo->GetBinContent(i) + histo->GetBinContent(i)*log(histo->GetBinContent(i)/mean));
	  nbinpieni++;
	}
      else chi2 += 2.*mean;
    }
  
  cout << " Chiquadro per fit con i minimi quadrati (bin a 0 NON contati) " << chi1 << " chi ridotto " << chi1 / (nbinpieni-1) << " p-value " << TMath::Prob(chi1,nbinpieni-1) << endl;
  cout << " Chiquadro per fit con likelihood (bin a 0 contati) "            << chi2 << " chi ridotto " << chi2 / (nbin-1)      << " p-value " << TMath::Prob(chi2,nbin-1) << endl;
}


int main (int argc, char** argv)
{
  TApplication* myApp = new TApplication("myApp", NULL, NULL);
  gStyle->SetOptFit(1111);
  
  TCanvas* c1 = new TCanvas("c1","My Canvas");
  c1->Divide(2,1);
  
  double min  = 0, max = 10;
  int Neventi = 0;
  int nbin    = max - min;
  double myrand;
  TH1D* histoC = new TH1D("histoC","histoC",nbin,min,max);
  TH1D* histoL = new TH1D("histoL","histoL",nbin,min,max);

  // Read data from file
  ifstream inF(argv[1]);
  if (inF.good() == false)
    {
      cout << "Error opening the file: " << argv[1] << endl;
      exit(1);
    }
  int nc = 0;
  while(true)
    {
      inF >> myrand;
      if (inF.eof() == true) break;
      histoC->Fill(myrand);
      histoL->Fill(myrand);
      nc++;
    }
  
  cout << "Number of events: " << nc << endl;
  Neventi = nc;
  inF.close();
  
  double atteso = Neventi / (max - min);
  cout << "Expected value: " << atteso << endl;

  
  // Coss-check ROOT error assigned to the bin
  double valore, errore;
  for (int i = 1; i <= nbin; i++)
    {
      valore = histoC->GetBinContent(i);
      errore = histoC->GetBinError(i);
      cout << i << ") " << valore << " +/- " << errore << endl;
      cout << "   " << errore - sqrt(valore) << endl;
    }

  
  c1->cd(1);
  histoC->Draw();
  c1->cd(2);
  histoL->Draw();


  TF1 *funzione = new TF1("pol0","pol0",0,10);
  double meanC, errC, chiC, ndfC;
  double meanL, errL, chiL, ndfL;
  
  
  histoC->Fit("pol0","S C");
  meanC = funzione->GetParameter(0);
  errC  = funzione->GetParError(0);
  chiC  = funzione->GetChisquare();
  ndfC  = funzione->GetNDF();

  cout << "\nFit chiquadro " << meanC << " errore " << errC << " chiq " << chiC << " chiq/ndf " << chiC/ndfC << endl;
  cout << " Numero di deviazioni dal valore atteso " << fabs(meanC-atteso)/errC << "\n" << endl;

  
  TFitResultPtr resultL = histoL->Fit("pol0","S L");
  meanL = funzione->GetParameter(0);
  errL  = funzione->GetParError(0);
  chiL  = 2. * resultL->MinFcnValue();
  ndfL  = funzione->GetNDF();

  cout << "\nFit likelihood " << meanL << " errore " << errL << " chiq " << chiL << " chiq/ndf " << chiL/ndfL << endl;
  cout << " Numero di deviazioni dal valore atteso " << fabs(meanL-atteso)/errL << endl;


  // Compute Chi-2
  cout << "\nCHIQUADRO FIT OPZIONE C " << endl;
  chiquadro(histoC, meanC);
  cout << "\nCHIQUADRO FIT OPZIONE L " << endl;
  chiquadro(histoL, meanL);

  
  c1->Modified();
  c1->Update();
  myApp->Run();
  return 0;
}
