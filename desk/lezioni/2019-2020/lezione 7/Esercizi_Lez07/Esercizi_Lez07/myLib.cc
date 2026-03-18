#include "myLib.h"

// #################################
// # Probability Density Functions #
// #################################
double Statistics::fExp (double x, double mu)
{
  return exp(-x/mu) / mu;
}

double Statistics::fGauss (double x, double mu, double sigma)
{
  return exp(-0.5*pow((x-mu),2)/(sigma*sigma)) / sqrt(2*M_PI*sigma*sigma);
}

double Statistics::fCauchy (double x)
{
  return 1 / (M_PI*(1.+x*x));
}


// #######################
// # Numeric integration #
// #######################
double Statistics::integrator_Exp (double start, double stop, double dx)
{
  double integral = 0;
  double MU       = 0.25;
  double x        = start;

  while (x < stop)
    {
      integral += Statistics::fExp(x,MU) * dx;
      x += dx;
    }

  return integral;
}

double Statistics::rand_FCI_Exp_Numeric (double error, double start, double target)
{
  double integral;
  double stop;
  double dx = 1;

  do
    {
      stop = start;

      do
        {
          stop += dx;
          integral = Statistics::integrator_Exp(start, stop, dx);
        }
      while (integral < target);

      dx /= 2;
    }
  while ((integral-target) > error);

  return stop;
}


// ##############
// # Generators #
// ##############
double Statistics::rand_range (double min, double max)
{
  return min + (max - min) * rand() / RAND_MAX;
}

double Statistics::rand_TAC_Gauss (double mu, double sigma)
{
  double xMin = mu-5*sigma;
  double xMax = mu+5*sigma;
  double yMin = 0.;
  double yMax = 1./sqrt(2*M_PI*sigma*sigma);
  double x = 0., y = 0.;

  do {
    x = Statistics::rand_range(xMin, xMax);
    y = Statistics::rand_range(yMin, yMax);
  } while (y > Statistics::fGauss(x, mu, sigma));

  return x;
}

double Statistics::rand_TAC_Cauchy (double xMin, double xMax, double yMin, double yMax)
{
  double x=0., y=0.;

  do
    {
      x = Statistics::rand_range(xMin, xMax);
      y = Statistics::rand_range(yMin, yMax);
    } while (y > Statistics::fCauchy(x));

  return x;
}

double Statistics::rand_FCI_Exp (double mu)
{
  double x, y;

  y = Statistics::rand_range(0, 1);
  x = -mu * log(1 - y);

  return x;
}

double Statistics::rand_CLT (double xMin, double xMax, int tries)
{
  double x = 0.;

  for (int i = 0; i < tries; i++)
    x += Statistics::rand_range(xMin, xMax);

  return x/tries;
}


// ##################################
// # Sorting algorithm: Bubble sort #
// ##################################
void Statistics::sortArray (double* myArray, int dim)
{
  bool flag = true;

  for (int i = 1; (i < dim && flag == true); i++)
    {
      flag = false;

      for (int j = 0; j < (dim - i); j++)
        {
          if (myArray[j+1] < myArray[j])
            {
              double temp  = myArray[j];
              myArray[j]   = myArray[j+1];
              myArray[j+1] = temp;

              flag = true;
            }
        }
    }
}


// ###############################################
// # Linear Congruential Generator               #
// # for the generation of pseudo-random numbers #
// ###############################################
long int Statistics::genLinCong (long int Xn)
{
  return (GENLINCONG::A*Xn + GENLINCONG::C) % GENLINCONG::M;
}
