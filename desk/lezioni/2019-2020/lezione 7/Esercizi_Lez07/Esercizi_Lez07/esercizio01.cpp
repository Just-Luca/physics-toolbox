/*
c++ -o esercizio01 esercizio01.cpp myLib.cc `root-config --glibs --cflags`
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

  double a = 0.;
  double b = 10.;

  TH1D h1 ("histogram", "rand_range", 100, a, b);

  double random, sum=0., sumSq=0.;
  for (unsigned int i = 0; i < MAX_NUM; i++)
    {
      random = Statistics::rand_range(a,b);
      sum   += random;
      sumSq += random*random;
      h1.Fill(random);
    }
  double mean = sum/MAX_NUM;
  double var  = sumSq/MAX_NUM - mean*mean;

  std::cout << "Media: " << mean << std::endl;
  std::cout << "(a+b)/2: " << 0.5*(a+b) << std::endl;

  std::cout << "Varianza: " << var << std::endl;
  std::cout << "(b-a)^2/12: " << (b-a)*(b-a)/12. << std::endl;

  TCanvas c1;
  h1.Draw();
  c1.Print("rand_range.png", "png");

  return 0;
}
