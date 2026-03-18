/*
c++ -o esempio01 esempio01.cpp istogramma.cc
*/

#include <random>
#include "istogramma.h"

#define N 10000


int main ()
{
  std::default_random_engine generator;

  const int Nbin     = 20;
  const double min   =  0;
  const double max   = 10;
  const double mean  =  5;
  const double sigma =  1;

  // Constructor with initialisation values
  istogramma MyHisto (Nbin, min, max);

  // Copy constructor
  istogramma HistoCopy (MyHisto);
  istogramma HistoCopy2 = MyHisto;

  std::normal_distribution<double> pdfGauss(mean,sigma);
  for (int i = 0; i < N; i++)
    MyHisto.Fill(pdfGauss(generator));
  MyHisto.Print();

  std::cout << "Mean = " << MyHisto.GetMean() << std::endl;
  std::cout << "RMS  = " << MyHisto.GetRMS() << std::endl;

  istogramma MyHisto2 (Nbin, min, max);
  std::uniform_real_distribution<double> pdfUniform(min,max);
  for (int i = 0; i < N; i++)
    MyHisto2.Fill(pdfUniform(generator));

  istogramma SumHisto;
  SumHisto = MyHisto + MyHisto2;

  SumHisto.Print();

  return 0;
}
