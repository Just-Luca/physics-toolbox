/*
c++ -o HitMiss HitMiss.cpp myLib.cc
*/

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>

#include "myLib.h"

#define MAX_NUM 100000

int main()
{
  srand(time(NULL));

  int nHit    = 0;
  double xMin = 0., xMax = 2*M_PI;
  double yMin = 0., yMax = 2.;

  for (int i = 0; i < MAX_NUM; i++)
    {
      if (Statistics::HitMiss_Sin(xMin, xMax, yMin, yMax) == true)
        nHit++;
    }

  double Area     = (xMax-xMin) * (yMax-yMin);
  double Integral = nHit * Area / static_cast<double>(MAX_NUM);
  double p        = nHit / static_cast<double>(MAX_NUM);
  double Var      = Area * Area / static_cast<double>(MAX_NUM) * p * (1-p);
  double StdDev   = sqrt(Var);

  std::cout << "Integral = " << Integral
            << " +- "<< StdDev << std::endl;
  return 0;
}
