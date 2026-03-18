#include <cstdlib>
#include <cmath>

#include <TMath.h>

using namespace std;

double rand_range(double min, double max){
  return min + (max-min) * rand() /(1. * RAND_MAX);
}

bool testCompatibility (double& pvalue, double meas1, double err1,
			  double meas2, double significance){
  double stat;
  stat   = fabs((meas1 - meas2) / err1);
  
  pvalue = TMath::Erfc(stat/sqrt(2));

  if (pvalue > significance){
    return true;
  } else {
    return false;
  }
}

