/*
c++ -o esercizio09 esercizio09.cpp myLib.cc vett2d.cc `root-config --cflags --glibs`
*/

#include <iostream>
#include <cmath>

#include "TApplication.h"
#include "TCanvas.h"
#include "TH1D.h"
#include "TGraph.h"
#include "TF1.h"

#include "vett2d.h"
#include "myLib.h"

#define MAX_NUM 10000
#define NSTEP    1000

int main()
{
  TApplication myApp("myApp",NULL,NULL);

  TCanvas c0("c0","c0",0,0,700,500);
  TCanvas c1("c1","c1",0,0,700,500);
  TCanvas c2("c2","c2",0,0,700,500);
  TCanvas c3("c3","c3",0,0,700,500);

  TH1D h0("h0","x",100,-60,60);
  TH1D h1("h1","y",100,-60,60);
  TH1D h2("h2","R",100,0,60);
  TGraph g0;

  for (int i = 0; i < MAX_NUM; i++)
    {
      vett2d position;

      for (int j = 0; j < NSTEP; j++)
        {
          if (i == 0) g0.SetPoint(g0.GetN(),position.getx(),position.gety());
          double theta = Statistics::rand_range(0,2*M_PI);
          vett2d step(cos(theta),sin(theta));
          position = position + step;
        }

      h0.Fill(position.getx());
      h1.Fill(position.gety());
      h2.Fill(position.mod());
    }

  c0.cd();
  h0.Draw();
  h0.Fit("gaus");
  c0.Modified();
  c0.Update();

  c1.cd();
  h1.Draw();
  h1.Fit("gaus");
  c1.Modified();
  c1.Update();

  c2.cd();
  h2.Draw();
  // h2.Fit("gaus");
  TF1 myFun("myFun","x*gaus(x)"); // Rayleigh distribution
  h2.Fit("myFun");
  c2.Modified();
  c2.Update();

  c3.cd();
  g0.GetXaxis()->SetLimits(-60,60);
  g0.GetHistogram()->SetMinimum(-60);
  g0.GetHistogram()->SetMaximum(60);
  g0.Draw("AL");
  c3.Modified();
  c3.Update();

  myApp.Run();

  return 0;
}
