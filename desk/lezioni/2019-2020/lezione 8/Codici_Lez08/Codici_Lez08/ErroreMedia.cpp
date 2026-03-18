/*
c++ -o ErroreMedia ErroreMedia.cpp myLib.cc `root-config --glibs --cflags`
*/

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>

#include "TApplication.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TH1D.h"

#include "myLib.h"

#define N 10000
#define Q 10000

int main()
{
  srand(time(NULL));

  double a = 0., b = 10.;
  double mean, random;

  TApplication myApp("myApp", NULL, NULL);
  TCanvas myCanv("myCanv","Canvas Title",0,0,700,500);
  TH1D h1("histogram", "Histogram Title", 100, a, b);

  for (int i = 0; i < N; i++)
    {
      mean = 0;
      for (int j = 0; j < Q; j++)
        {
          random = Statistics::rand_range(a,b);
          mean  += random;
        }
      mean /= Q;
      h1.Fill(mean);
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
