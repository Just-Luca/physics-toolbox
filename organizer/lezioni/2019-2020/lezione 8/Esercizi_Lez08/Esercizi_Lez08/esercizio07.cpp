/*
c++ -o esercizio07 esercizio07.cpp myLib.cc `root-config --glibs --cflags`
*/

#include <iostream>
#include <cmath>
#include <ctime>

#include "TApplication.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TH1D.h"

#include "myLib.h"

#define N  10000
#define Q  10000
#define MU 0.25

int main()
{
  srand(time(NULL));

  int nHit;
  double xMin = 0., xMax;
  double yMin = 0., yMax = 1/MU;
  double Area, Integral;

  TApplication myApp("myApp", NULL, NULL);
  TCanvas myCanv("myCanv","Canvas Title",0,0,700,500);
  TH1D h1("histogram", "Histogram Title", 100, 0, 1);

  for (unsigned int i = 0; i < N; i++)
    {
      nHit = 0;
      xMax = Statistics::rand_FCI_Exp(MU);

      for (unsigned int j = 0; j < Q; j++)
        {
          if (Statistics::HitMiss_Exp(xMin, xMax, yMin, yMax) == true)
            nHit++;
        }

      Area     = (xMax-xMin) * (yMax-yMin);
      Integral = nHit * Area / static_cast<double>(N);
      h1.Fill(Integral);
    }

  gStyle->SetOptFit(1111);
  myCanv.cd();
  h1.Draw();
  myCanv.Modified();
  myCanv.Update();
  myApp.Run();

  return 0;
}
