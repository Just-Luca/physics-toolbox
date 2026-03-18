/*
c++ -o esercizio06 esercizio06.cpp myLib.cc
*/

#include <iostream>
#include <cmath>
#include <ctime>

#include "myLib.h"

#define MAX_NUM 10000

int main()
{
  srand(time(NULL));

  double xMin = -5, xMax;
  double sum  = 0., sumSq = 0., y;

  std::cout << "Inserire l'estremo superiore che si vuole utilizzare per calcolare l'integrale della pdf Normale: ";
  std::cin >> xMax;

  for (int i = 0; i < MAX_NUM; i++)
    {
      y = Statistics::Crude_MC_Gauss(xMin, xMax);
      sum   += y;
      sumSq += y*y;
    }

  double mean = sum / MAX_NUM;
  double var  = (sumSq / MAX_NUM - mean*mean) * MAX_NUM / (MAX_NUM-1); // Unbiased estimator

  double ErrMean     = sqrt(var/MAX_NUM);
  double Integral    = (xMax-xMin)*mean;
  double ErrIntegral = (xMax-xMin)*ErrMean;

  std::cout << "Integrale della pdf Normale nel range [" << xMin << ", " << xMax << "]= " << Integral << " +/- " << ErrIntegral << std::endl;
  return 0;
}
