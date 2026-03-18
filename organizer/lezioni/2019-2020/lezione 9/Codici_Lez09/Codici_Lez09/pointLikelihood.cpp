/*
c++ -o pointLikelihood pointLikelihood.cpp myLib.cc `root-config --cflags --glibs`
*/

#include <iostream>
#include <fstream>
#include <cmath>

#include "TApplication.h"
#include "TCanvas.h"
#include "TH1D.h"
#include "TF1.h"
#include "TMath.h"
#include "TLine.h"

#include "myLib.h"

// #########################
// # Hard-coded parameters #
// #########################
#define PRECISION 1e-7
#define NBINS   100
#define NTOYS 10000
#define NSIGMAS   5
#define COVLEVEL 68

using namespace std;


double recoursiveBisection(TF1* myFun, double xMin, double xMax, double precision)
{
  double xMean = 0.5 * (xMin + xMax);

  if ((xMax - xMin) < precision) return xMean;

  if (myFun->Eval(xMean) * myFun->Eval(xMin) < 0)
    return recoursiveBisection(myFun, xMin, xMean, precision);

  return recoursiveBisection(myFun, xMean, xMax, precision);
}


void computeInterval(double muHat, int nSample, TF1* loglike, double* interval, double min, double max)
{
  loglike->SetParameters(nSample, muHat);

  TF1* loglikeShift = new TF1("loglikeShift", "loglike - 0.5 - [2]", min, max);
  loglikeShift->SetParameter(2, loglike->Eval(muHat));

  interval[0] = recoursiveBisection(loglikeShift, min, muHat, PRECISION);
  interval[1] = recoursiveBisection(loglikeShift, muHat, max, PRECISION);
}


int main(int argc, char** argv)
{
  // ######################################################
  // # Code to generate data file for a single experiment #
  // ######################################################
  // int nSample = 10;
  // double mu   =  5;
  // ofstream out;
  // out.open("data.txt",ios::out);
  // for (unsigned int i = 0; i < nSample; i++) out << Statistics::rand_FCI_Exp(mu) << endl;
  // out.close();
  // return 0;


  if (argc < 2)
    {
      cout << "Digitare il nome dei file da riga di comando" << endl;
      cout << "\t./pointLikelihood data.txt" << endl;
      return 1;
    }


  // ##############################
  // # Code to read the data file #
  // ##############################
  vector<double> data;
  double input;
  ifstream in;
  in.open(argv[1],ios::in);
  if (in.good() == false)
    {
      cout << "Problem opening the file: " << argv[1] << endl;
      return 1;
    }
  while (true)
    {
      in >> input;
      if (in.eof() == true) break;
      data.push_back(input);
    }
  in.close();


  TApplication* theApp = new TApplication("theApp", NULL, NULL);

  TCanvas* c1 = new TCanvas("c1","c1", 0, 0,700,500);
  TCanvas* c2 = new TCanvas("c2","c2",10,10,700,500);
  TCanvas* c3 = new TCanvas("c3","c3",20,20,700,500);


  // ########################
  // # Parameter estimation #
  // ########################
  double muHatData = 0;
  double sigmaHatData;
  for (unsigned int i = 0; i < data.size(); i++) muHatData += data[i];
  muHatData /= data.size();
  sigmaHatData = muHatData / sqrt(data.size());
  double min = (muHatData - NSIGMAS * sigmaHatData <= 0 ? PRECISION : muHatData - NSIGMAS * sigmaHatData);
  double max =  muHatData + NSIGMAS * sigmaHatData;


  // #################################################################
  // # Compute uncerainties on the estimated parameter mu with the   #
  // # method of projection of the contour Delta_log(Likelihood)=0.5 #
  // #################################################################
  TF1* loglike = new TF1("loglike", "[0]*(log(x) + [1]/x)", min, max);
  double interval[2];
  computeInterval(muHatData, data.size(), loglike, interval, min, max);


  // ####################################
  // # Shift -log(Likelihood) verticaly #
  // ####################################
  TF1* loglikeShift = new TF1("loglikeShift", "loglike - 0.5 - [2]", min, max);
  loglikeShift->SetParameter(2, loglike->Eval(muHatData));
  loglikeShift->SetTitle("-log(Likelihood) shifted vertically");
  loglikeShift->GetXaxis()->SetTitle("#mu");
  loglikeShift->GetYaxis()->SetTitle("-log(Likelihood)");
  loglikeShift->SetLineColor(kBlack);
  loglikeShift->GetYaxis()->SetRangeUser(-1,1);

  TLine* lineBest = new TLine(muHatData, 0, muHatData, loglikeShift->Eval(muHatData));
  lineBest->SetLineColor(kRed);


  c1->cd();
  loglikeShift->Draw();
  lineBest->Draw("same");
  c1->SetGrid();
  c1->Modified();
  c1->Update();


  cout << "\n##############################################################" << endl;
  cout << "### Point likelihood method for the model: exponential pdf ###" << endl;
  cout << "##############################################################" << endl;
  cout << "--> Parameter estimation: mu_hat = " << muHatData << " +/- " << sigmaHatData << endl;
  cout << "--> Uncertainty on the estimate of mu from Delta_log(Likelihood) = 0.5 projection: +"
       << interval[1]-muHatData << " / " << interval[0]-muHatData
       << " i.e. the interval [" << interval[0] << ", " << interval[1] << "]\n" << endl;


  // #############################################################################
  // # Using pseudo-experiments (i.e. toy Monte Carlo) to determine numerically: #
  // # - the pdf of the estimator of the paramter mu                             #
  // # - the coverage of the uncertainty on the estimate of mu                   #
  // #############################################################################
  double muHatToys;
  double coverage = 0;
  TH1D* hpdfMu = new TH1D("hpdfMu", "Numeric pdf of the estimator of #mu", NBINS, min, max);
  hpdfMu->GetXaxis()->SetTitle("Estimated #mu");
  hpdfMu->GetYaxis()->SetTitle("Entries [#]");
  TH1D* hpulls = new TH1D("hpulls", "Pull distribution for the estimate of #mu", NBINS, -3, 3);
  hpulls->GetXaxis()->SetTitle("Pull of the estimate of #mu");
  hpulls->GetYaxis()->SetTitle("Entries [#]");
  // for loop for NTOYS pseudo-experiments
  for (unsigned int j = 0; j < NTOYS; j++)
    {
      muHatToys = 0;
      // for loop for a single pseudo-experiment made of data.size() measurements
      for (unsigned int i = 0; i < data.size(); i++) muHatToys += Statistics::rand_FCI_Exp(muHatData);
      muHatToys /= data.size();
      hpdfMu->Fill(muHatToys);

      computeInterval(muHatToys, data.size(), loglike, interval, min, max);
      if (interval[0] < muHatData && interval[1] > muHatData) coverage++;

      hpulls->Fill((muHatToys-muHatData) / (muHatToys > muHatData ? muHatToys-interval[0] : interval[1]-muHatToys));
    }

  c2->cd();
  hpdfMu->Draw();


  // ###################################
  // # Fit pdf estimator with Gaussian #
  // ###################################
  TF1* fitGauss = new TF1("fitGauss", "gaus", min, max);
  hpdfMu->Fit(fitGauss,"L");
  fitGauss->Draw("same");


  // ################################
  // # Fit pdf estimator with Gamma #
  // ################################
  TF1* fitGamma = new TF1("fitGamma", "[2]*TMath::GammaDist(x,[0],0,[1])", min, max);
  fitGamma->SetParameters(data.size(), muHatData/data.size(), NTOYS/data.size());
  fitGamma->SetLineColor(kBlue);
  hpdfMu->Fit(fitGamma,"L+");
  fitGamma->Draw("same");


  c2->Modified();
  c2->Update();

  c3->cd();
  hpulls->Draw();
  hpulls->Fit("gaus");
  c3->Modified();
  c3->Update();


  theApp->Run();
  return 0;
}
