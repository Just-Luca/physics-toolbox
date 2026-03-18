/*
c++ -o esercizio08 esercizio08.cpp myLib.cc `root-config --cflags --glibs`
*/

#include <iostream>
#include <cmath>

#include "TApplication.h"
#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TH1D.h"
#include "TMath.h"

#include "myLib.h"

#define N_MAX 2000

int main ()
{
  TApplication myApp("myApp",NULL,NULL);

  srand(1);
  double xMin = -1, xMax = 1;


  // ######################
  // # Metodo Hit or Miss #
  // ######################
  TGraphErrors myGraphHitOrMiss;
  TGraph       myGraphHitOrMiss_pval;
  TH1D         myGraphHitOrMiss_resi("myGraphHitOrMiss_resi","Monte Carlo",100,-3,3);
  for (int N = 10; N < N_MAX; N+=10)
    {
      int nHit    = 0;
      double yMin = 0., yMax = 2.;

      for (int i = 0; i < N; i++)
        {
          if (Statistics::HitMiss_PI(xMin, xMax, yMin, yMax) == true)
            nHit++;
        }

      double Area        = (xMax-xMin) * (yMax-yMin);
      double Integral    = nHit * Area / static_cast<double>(N);
      double p           = nHit / static_cast<double>(N);
      double Var         = Area * Area / static_cast<double>(N) * p * (1-p);
      double ErrIntegral = sqrt(Var);

      myGraphHitOrMiss.SetPoint(myGraphHitOrMiss.GetN(),N,Integral-M_PI);
      myGraphHitOrMiss.SetPointError(myGraphHitOrMiss.GetN()-1,0,ErrIntegral);

      myGraphHitOrMiss_pval.SetPoint(myGraphHitOrMiss_pval.GetN(),N,ErrIntegral);
      myGraphHitOrMiss_resi.Fill((Integral-M_PI)/ErrIntegral);
    }


  // ############################
  // # Metodo crude Monte Carlo #
  // ############################
  TGraphErrors myGraphCrudeMC;
  TGraph       myGraphCrudeMC_pval;
  TH1D         myGraphCrudeMC_resi("myGraphCrudeMC_resi","Monte Carlo",100,-3,3);
  for (int N = 10; N < N_MAX; N+=10)
    {
      double sum = 0., sumSq = 0., y;

      for (int i = 0; i < N; i++)
        {
          y = Statistics::Crude_MC_PI(xMin, xMax);
          sum   += y;
          sumSq += y*y;
        }

      double mean = sum / N;
      double var  = (sumSq / N - mean*mean) * N / (N-1); // Unbiased estimator

      double ErrMean     = sqrt(var/N);
      double Integral    = (xMax-xMin)*mean;
      double ErrIntegral = (xMax-xMin)*ErrMean;

      myGraphCrudeMC.SetPoint(myGraphCrudeMC.GetN(),N,Integral-M_PI);
      myGraphCrudeMC.SetPointError(myGraphCrudeMC.GetN()-1,0,ErrIntegral);

      myGraphCrudeMC_pval.SetPoint(myGraphCrudeMC_pval.GetN(),N,ErrIntegral);
      myGraphCrudeMC_resi.Fill((Integral-M_PI)/ErrIntegral);
    }


  TCanvas c0("c0","c0",0,0,700,500);
  c0.cd();

  myGraphHitOrMiss.SetTitle("Monte Carlo;Extractions;Residuals;none");
  myGraphHitOrMiss.SetMarkerStyle(20);
  myGraphHitOrMiss.SetMarkerSize(0.4);
  myGraphHitOrMiss.SetMarkerColor(kBlack);
  myGraphHitOrMiss.Draw("APE");

  myGraphCrudeMC.SetTitle("Monte Carlo;Extractions;Residuals;none");
  myGraphCrudeMC.SetMarkerStyle(21);
  myGraphCrudeMC.SetMarkerSize(0.4);
  myGraphCrudeMC.SetMarkerColor(kRed);
  myGraphCrudeMC.Draw("PE");

  c0.SetGrid();
  c0.Modified();
  c0.Update();


  TCanvas c1("c1","c1",0,0,700,500);
  c1.cd();

  myGraphHitOrMiss_pval.SetTitle("Monte Carlo;Extractions;Error;none");
  myGraphHitOrMiss_pval.SetLineColor(kBlack);
  myGraphHitOrMiss_pval.Draw("AL");

  myGraphCrudeMC.SetTitle("Monte Carlo;Extractions;Error;none");
  myGraphCrudeMC_pval.SetLineColor(kRed);
  myGraphCrudeMC_pval.Draw("L");

  c1.Modified();
  c1.Update();


  TCanvas c2("c2","c2",0,0,700,500);
  c2.cd();

  myGraphHitOrMiss_resi.SetXTitle("(y_{i} - #pi)/#sigma");
  myGraphHitOrMiss_resi.SetYTitle("Entries");
  myGraphHitOrMiss_resi.SetLineColor(kBlack);
  myGraphHitOrMiss_resi.Draw();
  myGraphHitOrMiss_resi.Fit("gaus");

  c2.Modified();
  c2.Update();


  TCanvas c3("c3","c3",0,0,700,500);
  c3.cd();

  myGraphCrudeMC_resi.SetXTitle("(y_{i} - #pi)/#sigma");
  myGraphCrudeMC_resi.SetYTitle("Entries");
  myGraphCrudeMC_resi.SetLineColor(kRed);
  myGraphCrudeMC_resi.Draw();
  myGraphCrudeMC_resi.Fit("gaus");

  c3.Modified();
  c3.Update();


  myApp.Run();
  return 0;
}
