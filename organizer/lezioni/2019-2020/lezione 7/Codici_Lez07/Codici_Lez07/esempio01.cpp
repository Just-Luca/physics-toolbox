/*
c++ -o esempio01 esempio01.cpp
*/

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <cmath>

#define MAX_NUM 100000

double fGaus(double x)
{
  return exp(-0.5*x*x);
}

double rand_range(double min, double max)
{
  return min + (max - min) * rand() / RAND_MAX;
}

double rand_TAC_Gauss(double xMin, double xMax, double yMin, double yMax)
{
  double x = 0., y = 0.;
  do {
    x = rand_range(xMin, xMax);
    y = rand_range(yMin, yMax);
  } while (y > fGaus(x));
  return x;
}

int main()
{
  srand(time(NULL));
  double rnd_number;

  for (int i = 0; i < MAX_NUM; i++)
    {
      rnd_number = rand_TAC_Gauss(-1., 1., 0., 1.);
      std::cout << "Random number: "
                << rnd_number << std::endl;
    }

  return 0;
}
