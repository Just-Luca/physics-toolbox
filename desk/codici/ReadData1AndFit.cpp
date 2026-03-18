#include <iostream>
#include <fstream>
#include <TStyle.h>
#include <TApplication.h>
#include <TCanvas.h>
#include <TH1D.h>
#include <TF1.h>
#include <cmath>
#include "myLib.h"

/*double myGauss (double* x, double* par)
{
  return par[0] * exp(-0.5*((x[0]-par[1])*(x[0]-par[1])/(par[2]*par[2])));
}

double myParabola (double* x, double* par)
{
  return par[0] + par[1]*x[0] + par[2]*x[0]*x[0];
}

double sum (double* x, double* par)
{
  double val = myGauss(x, par) + myParabola(x, &par[3]);
  return val;
}

bool ReadData(char* fileName, TH1D* myHisto)
{
  double val;
  std::fstream f;
  f.open(fileName,std::ios::in);
  if (f.good() == false) return false;
  while (true)
    {
      f >> val;
      if (f.eof() == true) break;
      myHisto->Fill(val);
    }
  return true;
}

void ComputeChi2(TH1D* myHisto, TF1* myFun, double& chi2, double& NDF)
{
  double result = 0;
  for (unsigned int i = 1; i <= myHisto->GetNbinsX(); i++)
    {
      result += pow((myHisto->GetBinContent(i) - myFun->Eval(myHisto->GetBinCenter(i))),2.) / myHisto->GetBinContent(i);
    }

  chi2 = result;
  NDF  = myHisto->GetNbinsX() - myFun->GetNpar();
}

*/
int main(int argc, char** argv)
{
  int nBins   = 100;
  double xMin = 0;
  double xMax = 10;

  if (argc < 2)
    {
      std::cout << "Insufficient number of parameters: ./RedData1AndFit fileName.txt" << std::endl;
      return 1;
    }
 
  gStyle->SetOptFit(1112);

  TApplication* myApp = new TApplication("myApp", NULL, NULL);  
  TCanvas* myCanv = new TCanvas("myCanv","myCanv",0,0,700,500);
  TH1D* myHisto = new TH1D("myHisto","myHisto",nBins,xMin,xMax);

  TF1* myFun = new TF1("myFun",sum,xMin,xMax,6);
  myFun->SetParameter(0,1);
  myFun->SetParameter(1,5);
  myFun->SetParameter(2,1);

  myFun->SetParameter(3,0);
  myFun->SetParameter(4,1);
  myFun->SetParameter(5,-1);

  myFun->SetParName(0,"Ampl");
  myFun->SetParName(1,"Mean");
  myFun->SetParName(2,"Sigma");

  myFun->SetParName(3,"Zero");
  myFun->SetParName(4,"First");
  myFun->SetParName(5,"Second");

  if (ReadData(argv[1],myHisto) == false)
    {
      std::cout << "Error reading data file" << std::endl;
      return 1;
    }

  myCanv->cd();
  myHisto->Draw();
  myHisto->Fit("myFun");
  
  myCanv->Modified();
  myCanv->Update();

  std::cout << "Reduced Chi-2: ";
  std::cout << myFun->GetChisquare()/myFun->GetNDF() << std::endl;
  std::cout << "p-value: " << myFun->GetProb() << std::endl;

  // Compute number of entries for the signal (i.e. Gaussian)
  TF1* mySignal = new TF1("mySignal",myGauss,xMin,xMax,3);
  mySignal->SetParameter(0,myFun->GetParameter(0));
  mySignal->SetParameter(1,myFun->GetParameter(1));
  mySignal->SetParameter(2,myFun->GetParameter(2));
  std::cout << "Number of entries for the signal (i.e. Gaussian): ";
  std::cout << nBins / (xMax - xMin) * mySignal->Integral(xMin, xMax);
  std::cout << std::endl;
  
  // Compute number of entries for the background (i.e. Parabola)
  TF1* myBackground = new TF1("myBackground",myParabola,xMin,xMax,3);
  myBackground->SetParameter(0,myFun->GetParameter(3));
  myBackground->SetParameter(1,myFun->GetParameter(4));
  myBackground->SetParameter(2,myFun->GetParameter(5));
  std::cout << "Number of entries for the background (i.e. Parabola): ";
  std::cout << nBins / (xMax - xMin) * myBackground->Integral(xMin, xMax);
  std::cout << std::endl;

  double chi2, NDF;
  ComputeChi2(myHisto,myFun,chi2,NDF);
  std::cout << "My Chi-2: " << chi2 << std::endl;
  std::cout << "My NDF: " << NDF << std::endl;

  myApp->Run();
  return 0;
}
