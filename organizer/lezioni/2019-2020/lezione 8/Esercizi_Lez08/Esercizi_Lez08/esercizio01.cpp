/*
c++ -o esercizio01 esercizio01.cpp myLib.cc `root-config --glibs --cflags`
*/

#include <iostream>
#include <cmath>
#include <ctime>

#include "TApplication.h"
#include "TCanvas.h"
#include "TH1D.h"

#include "myLib.h"

#define MAX_NUM 10000

int main()
{
  srand(time(NULL));

  int Q;

  std::cout << "Digitare quanti numeri campionare da una pdf uniforme: ";
  std::cin >> Q;

  double a = 0., b = 10.;
  double mean, random, mu = 0., sigmaMu = 0.;

  TApplication myApp("myApp", NULL, NULL);
  TCanvas myCanv("myCanv","Canvas Title",0,0,700,500);
  TH1D h1("histogram", "Histogram Title", 100, a, b);

  for (int i = 0; i < MAX_NUM; i++)
    {
      mean = 0;
      for (int j = 0; j < Q; j++)
        {
          random = Statistics::rand_range(a,b);
          mean  += random;
        }
      mean /= Q;
      h1.Fill(mean);
      mu += mean;
      sigmaMu += mean*mean;
    }

  mu /= MAX_NUM;
  sigmaMu = sqrt((sigmaMu/MAX_NUM - mu*mu) * MAX_NUM / (MAX_NUM-1)); // Unbiased estimator

  std::cout << "Per il TCL, la deviazione std della media di " << Q << " numeri estratti da una pdf uniforme nel range ["
            << a << ", " << b << "] e`: " << sqrt(1./Q) * (b-a)/sqrt(12.) << std::endl;
  std::cout << "Il valore stimato per la dev std della media campionando la pdf della media e`: " << sigmaMu << std::endl;

  myCanv.cd();
  h1.Draw();
  myCanv.Modified();
  myCanv.Update();
  myApp.Run();

  return 0;
}
