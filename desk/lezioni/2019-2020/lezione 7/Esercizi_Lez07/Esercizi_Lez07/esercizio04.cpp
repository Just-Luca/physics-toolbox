/*
c++ -o esercizio04 esercizio04.cpp myLib.cc `root-config --glibs --cflags`
*/

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>

#include "TCanvas.h"
#include "TH1D.h"

#include "myLib.h"

#define MAX_NUM 10000

int main ()
{
  srand(time(NULL));

  int Q;

  std::cout << "Quanti numeri casuali vuoi estrarre e mediare? ";
  std::cin >> Q;

  double xMin = 0.;
  double xMax = 1.;
  double mu   = 0.25;

  TH1D h1 ("histogram", "rand_TCL", 100, xMin, xMax);

  double random, sum=0., sumSq=0.;
  for (int i = 0; i < MAX_NUM; i++)
    {
      random = 0.;
      for (int j = 0; j < Q; j++)
        random += Statistics::rand_FCI_Exp(mu);
      random /= (double)Q;

      sum   += random;
      sumSq += random*random;
      h1.Fill(random);
    }
  double mean = sum/MAX_NUM;
  double var  = sumSq/MAX_NUM - mean*mean;

  std::cout << "Media: "    << mean << std::endl;
  std::cout << "Varianza: " << var  << std::endl;

  TCanvas c1;
  h1.Draw();
  c1.Print("rand_TCL.png", "png");

  return 0;
}
