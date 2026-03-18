/*
c++ -o fitTGraphErrors fitTGraphErrors.cpp `root-config --cflags --glibs`
*/

#include <iostream>
#include <cmath>

#include <TStyle.h>
#include <TApplication.h>
#include <TCanvas.h>
#include <TF1.h>
#include <TGraphErrors.h>
#include <TAxis.h>
#include <TFitResult.h>
#include <TMatrixDSym.h>

using namespace std;

double cauchy(double* x, double* par)
{
  double val = par[0] + par[1]/(x[0]*x[0]);
  // ### Test fit pathologies ###
  // double val = par[0] + 1000*log(par[1])/(x[0]*x[0]);
  // double val = par[0]*par[1] + 8023/(x[0]*x[0]);
  // ############################
  return val;
}

void ComputeChi2(TGraphErrors* myData, TF1* myFun, double& chi2, double& NDF)
{
  double result = 0;

  for (int i = 0; i < myData->GetN(); i++)
    {
      result += pow(myData->GetY()[i] - myFun->Eval(myData->GetX()[i]),2.) /
	(pow(myData->GetErrorY(i),2.) + pow(myFun->Derivative(myData->GetX()[i])*myData->GetErrorX(i),2.));
    }
  
  chi2 = result;
  NDF  = myData->GetN() - myFun->GetNpar();
}

// ### Exercise ###
/*
TGraph* ComputeContour(TGraphErrors* myData, TF1* myFun, double delta)
{
  int nPoints  = 600;
  int nSigma   = 2;
  double xMin  = myFun->GetParameter(0) - nSigma * myFun->GetParError(0);
  double yMin  = myFun->GetParameter(1) - nSigma * myFun->GetParError(1);
  double xStep = 2.*nSigma*myFun->GetParError(0) / nPoints;
  double yStep = 2.*nSigma*myFun->GetParError(1) / nPoints;
  
  double minChi2, NDF;
  ComputeChi2(myData,myFun,minChi2,NDF);
  
  double ContourLevel = minChi2 + delta;

  TGraph* least2Contour2D = new TGraph;
  least2Contour2D->GetXaxis()->SetTitle("Const");
  least2Contour2D->GetYaxis()->SetTitle("Scale (nm^2)");
  least2Contour2D->SetMarkerStyle(20);
  least2Contour2D->SetMarkerSize(0.3);

  double newChi2, par0, par1;
  unsigned int it = 0;
  for (unsigned int i = 0; i < nPoints; i++)
    {
      bool belowLevel = false;
      
      myFun->SetParameter(0,xMin + xStep*i);
      for (unsigned int j = 0; j < nPoints; j++)
	{
	  myFun->SetParameter(1,yMin + yStep*j);
	  ComputeChi2(myData,myFun,newChi2,NDF);
	  
	  if (((newChi2 - ContourLevel) < 0) && (belowLevel == false))
	    {
	      belowLevel = true;
	      par0 = myFun->GetParameter(0);
	      par1 = myFun->GetParameter(1);
	      least2Contour2D->SetPoint(it,par0,par1);
	      it++;
	    }
	  else if (((newChi2 - ContourLevel) > 0) && (belowLevel == true))
	    {
	      belowLevel = false;
	      par0 = myFun->GetParameter(0);
	      par1 = myFun->GetParameter(1);
	      least2Contour2D->SetPoint(it,par0,par1);
	      it++;
	    }
	  else continue;
	}
    }
  
  return least2Contour2D;
}
*/
// #################

int main(int argc, char** argv)
{
  if (argc < 2)
    {
      cout << "Not enough parameters: ./MyTGraphErrors filename.txt" << endl;
      return 1;
    }

  gStyle->SetOptFit(1112);
  
  TApplication* myApp = new TApplication("myApp", NULL, NULL);
  TCanvas* myC0 = new TCanvas("myC0","myC0",0,0,700,500);
  TF1* myFun = new TF1("myFun",cauchy,400,1000,2);
  myFun->SetParameter(0,1.6);
  myFun->SetParameter(1,8e3);
  myFun->SetParName(0,"Const");
  myFun->SetParName(1,"Scale");

  // TGraphErrors constructor from file
  TGraphErrors* myGraph = new TGraphErrors(argv[1]);
  myGraph->GetXaxis()->SetTitle("lambda (nm)");
  myGraph->GetYaxis()->SetTitle("Refractive index");
  myGraph->SetMarkerStyle(20);
  myGraph->SetMarkerSize(0.4);
  
  myC0->cd();
  myGraph->Draw("AP");
  TFitResultPtr r = myGraph->Fit("myFun","S");
  myC0->Modified();
  myC0->Update();

  std::cout << "Reduced Chi-2: ";
  std::cout << myFun->GetChisquare()/myFun->GetNDF() << std::endl;
  std::cout << "p-value: " << myFun->GetProb() << std::endl;

  double chi2, NDF;
  ComputeChi2(myGraph,myFun,chi2,NDF);
  std::cout << "My Chi-2: " << chi2 << std::endl;
  std::cout << "My NDF: " << NDF << std::endl;
  
  r->Print("V");
      
  // ### Exercise ###
  /*
  TCanvas* myC1 = new TCanvas("myC1","myC1",10,10,700,500);
  TGraph* least2Contour2D = ComputeContour(myGraph,myFun,1);
  myC1->cd();
  least2Contour2D->Draw("AP");
  myC1->Modified();
  myC1->Update();
  */
  // #################

  myApp->Run();
  return 0;
}

