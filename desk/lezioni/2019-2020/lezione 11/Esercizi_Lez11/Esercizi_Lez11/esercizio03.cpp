/*
c++ -o esercizio03 esercizio03.cpp myLib.cc `root-config --glibs --cflags`
*/

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>

#include "TApplication.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TH1D.h"
#include "TMath.h"

#include "myLib.h"

#define N  10000
#define MU     0.
#define SIGMA  1.
#define SCALE  1.

int main()
{
  srand(time(NULL));

  double measurement, chi2;
  double Integral;

  TApplication myApp("myApp",NULL,NULL);
  TH1D h1 ("histogram", "title", 100, 0, 1);
  h1.SetXTitle("p-value");
  h1.SetYTitle("Entries [#]");

  for (unsigned int i = 0; i < N; i++)
    {
      measurement = Statistics::rand_TAC_Gauss (MU, SIGMA);
      chi2        = (measurement - MU)*(measurement - MU) / (SIGMA*SIGMA*SCALE*SCALE);
      Integral    = TMath::Prob(chi2,1);
      h1.Fill(Integral);
    }


  TCanvas c1;
  h1.Draw();
  c1.Modified();
  c1.Update();


  myApp.Run();
  return 0;
}
