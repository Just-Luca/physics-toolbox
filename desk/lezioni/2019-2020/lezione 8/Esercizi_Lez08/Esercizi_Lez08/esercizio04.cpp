/*
c++ -o esercizio04 esercizio04.cpp myLib.cc `root-config --glibs --cflags`
*/

#include <iostream>
#include <cmath>
#include <ctime>

#include "TApplication.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TH1D.h"

#include "myLib.h"

#define MAX_NUM 10000

int main()
{
  srand(time(NULL));

  double mu = 0., sigma1 = 0.5, sigma2 = 2.;
  double random;

  TApplication myApp("myApp", NULL, NULL);
  TCanvas myCanv("myCanv","Canvas Title",0,0,700,500);
  TH1D h1("histogram", "Histogram Title", 100, mu-5*sigma2, mu+5*sigma2);

  for (int i = 0; i < MAX_NUM; i++)
    {
      double sum = 0.;

      random = Statistics::rand_TAC_Gauss(mu, sigma1);
      sum  += random;

      random = Statistics::rand_TAC_Gauss(mu, sigma2);
      sum  += random;

      h1.Fill(sum);
    }

  gStyle->SetOptFit(1111);
  myCanv.cd();
  h1.Draw();
  h1.Fit("gaus");
  myCanv.Modified();
  myCanv.Update();
  myApp.Run();

  return 0;
}
