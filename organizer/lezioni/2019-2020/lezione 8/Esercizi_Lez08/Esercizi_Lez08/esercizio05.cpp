/*
c++ -o esercizio05 esercizio05.cpp myLib.cc
*/

#include <iostream>
#include <cmath>
#include <ctime>

#include "myLib.h"

#define MAX_NUM 10000

int main()
{
  srand(time(NULL));

  int nHit    = 0;
  double xMin = -5, xMax;
  double yMin = 0., yMax = 1/sqrt(2*M_PI);

  std::cout << "Inserire l'estremo superiore che si vuole utilizzare per calcolare l'integrale della pdf Normale: ";
  std::cin >> xMax;

  for (int i = 0; i < MAX_NUM; i++)
    {
      if (Statistics::HitMiss_Gauss(xMin, xMax, yMin, yMax) == true)
        nHit++;
    }

  double Area        = (xMax-xMin) * (yMax-yMin);
  double Integral    = nHit * Area / static_cast<double>(MAX_NUM);
  double p           = nHit / static_cast<double>(MAX_NUM);
  double Var         = Area * Area / static_cast<double>(MAX_NUM) * p * (1-p);
  double ErrIntegral = sqrt(Var);

  std::cout << "Integrale della pdf Normale nel range [" << xMin << ", " << xMax << "]= " << Integral << " +/- " << ErrIntegral << std::endl;
  return 0;
}
