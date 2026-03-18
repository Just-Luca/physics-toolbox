#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

#include "MyFunz.h"

//prodotto potenza per esponenziale
double dist1(double* x, double* par)
{
  return (par[0]*pow(x[0],2))*(exp(-par[1]*x[0]));
}


double dist2(double* x, double* par)
{
	return par[0]*x[0]*exp(-par[1]*x[0]);
}


double dist3(double* x,double* par)
{
	return par[0]*pow(x[0],2)*exp(-par[1]*pow(x[0],2));
}

//gaussiana
double myGauss(double* x, double* par)
{
	return par[0]*exp(-0.5*(pow((x[0]-par[1])/ par[2], 2)));
}

//somma gaussiana e parabola
double gauss_parabola(double* x, double* par)
{
	//double var = par[0]*exp(-0.5*(pow((x[0]-par[1])/ par[2], 2)));
	//var += par[3]*x[0]*x[0] + par[4]*x[0] + par[5];

	double var = myGauss(x, par) + myParabola(x, par+3);
	return var;
}

//parabola
double myParabola(double* x, double* par)
{
	return par[0]*x[0]*x[0] + par[1]*x[0] + par[2];
}

//esponenziale
double myExp(double* x, double* par)
{
	return par[0] * exp(-x[0]/par[1]);
}

//somma due gaussiane e esponenziale
double sum(double* x, double* par)
{
	double val = myGauss(x, par) + myGauss(x, par+3) + myExp(x, par+6);
	return val;
}
