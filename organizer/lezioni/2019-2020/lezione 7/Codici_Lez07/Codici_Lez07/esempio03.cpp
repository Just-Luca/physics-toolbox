/*
c++ -o esempio03 esempio03.cpp `root-config --glibs --cflags`
*/

#include <iostream>
#include <cstdlib>
#include <ctime>

#include "TCanvas.h"
#include "TH1D.h"

#define MAX_NUM 100000

double rand_range(double min, double max)
{
  return min + (max - min) * rand() / RAND_MAX;
}

double rand_CLT(double xMin, double xMax, int tries)
{
  double x = 0.;

  for (int i = 0; i < tries; i++)
    x += rand_range(xMin, xMax);

  return x / tries;
}

int main()
{
  srand(time(NULL));
  double min        = -1;
  double max        =  1;
  int nEstrazioni   = 10;
  double rnd_number;

  TH1D pdf ("histogram", "title", 100, min, max);

  for (int i = 0; i < MAX_NUM; i++)
    {
      rnd_number = rand_CLT(min, max, nEstrazioni);
      std::cout << "Random number: "
                << rnd_number << std::endl;
      pdf.Fill(rnd_number);
    }

  TCanvas cnv;
  pdf.Draw();
  pdf.Fit("gaus");
  cnv.Print("histogram.png","png");

  return 0;
}
