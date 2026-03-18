/*
c++ -o esercizio02 esercizio02.cpp myLib.cc `root-config --glibs --cflags`
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
  double mu, sigma;

  std::cout << "Digitare quanti numeri campionare da una pdf Normale: ";
  std::cin >> Q;
  std::cout << "Impostare MU e SIGMA della pdf Normale: ";
  std::cin >> mu >> sigma;

  double mean, random, MeanMu=0., sigmaMu=0.;

  TApplication myApp("myApp", NULL, NULL);
  TCanvas myCanv("myCanv","Canvas Title",0,0,700,500);
  TH1D h1("histogram", "Histogram Title", 100, mu - 5*sigma/sqrt(static_cast<double>(Q)), mu + 5*sigma/sqrt(static_cast<double>(Q)));

  for (int i = 0; i < MAX_NUM; i++)
    {
      mean = 0;
      for (int j = 0; j < Q; j++)
        {
          random = Statistics::rand_TAC_Gauss(mu, sigma);
          mean += random;
        }
      mean /= Q;
      h1.Fill(mean);
      MeanMu  += mean;
      sigmaMu += mean*mean;
    }

  MeanMu /= MAX_NUM;
  sigmaMu = sqrt((sigmaMu/MAX_NUM - MeanMu*MeanMu) * MAX_NUM / (MAX_NUM-1)); // Unbiased estimator

  std::cout << "Per il TCL, la deviazione std della media di " << Q << " numeri estratti da una pdf Normale con sigma = "
            << sigma << " e`: " << sigma/sqrt(static_cast<double>(Q)) << std::endl;
  std::cout << "Il valore stimato per la dev std della media campionando la pdf della media e`: " << sigmaMu << std::endl;
  std::cout << "Il rapporto tra dev std della pdf Nornale di partenza e dev std della media e`: " << sigma/sigmaMu << std::endl;

  myCanv.cd();
  h1.Draw();
  myCanv.Modified();
  myCanv.Update();
  myApp.Run();

  return 0;
}
