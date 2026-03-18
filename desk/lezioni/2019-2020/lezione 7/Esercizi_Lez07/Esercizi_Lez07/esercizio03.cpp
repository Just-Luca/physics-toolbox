/*
c++ -o esercizio03 esercizio03.cpp myLib.cc `root-config --glibs --cflags`
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

  double xMin = 0.;
  double xMax = 1.;
  double mu   = 0.25;

  TH1D h1 ("histogram", "rand_FCI_Exp", 100, xMin, xMax);

  double random, sum=0., sumSq=0.;
  for (unsigned int i = 0; i < MAX_NUM; i++)
    {
      random = Statistics::rand_FCI_Exp(mu);
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
  c1.Print("rand_FCI_Exp.png", "png");

  return 0;
}
