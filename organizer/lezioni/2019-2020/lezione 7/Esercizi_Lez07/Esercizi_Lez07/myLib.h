#ifndef MYLIB_H
#define MYLIB_H

#include <iostream>
#include <ctime>
#include <cmath>

namespace Statistics
{
  // #################################
  // # Probability Density Functions #
  // #################################
  double fExp            (double x, double mu);
  double fGauss          (double x, double mu, double sigma);
  double fCauchy         (double x);


  // #######################
  // # Numeric integration #
  // #######################
  double integrator_Exp       (double start, double stop, double dx);
  double rand_FCI_Exp_Numeric (double error, double start, double target);


  // ##############
  // # Generators #
  // ##############
  double rand_range      (double min, double max);
  double rand_TAC_Gauss  (double mu, double sigma);
  double rand_TAC_Cauchy (double xMin, double xMax, double yMin, double yMax);
  double rand_FCI_Exp    (double mu);
  double rand_CLT        (double xMin, double xMax, int tries);


  // ##################################
  // # Sorting algorithm: Bubble sort #
  // ##################################
  void sortArray (double* myArray, int dim);


  // ###############################################
  // # Linear Congruential Generator               #
  // # for the generation of pseudo-random numbers #
  // ###############################################
  namespace GENLINCONG
  {
    const long int M = 2147483647;
    const long int A = 214013;
    const long int C = 2531011;
  }
  long int genLinCong (long int Xn);
}

#endif
