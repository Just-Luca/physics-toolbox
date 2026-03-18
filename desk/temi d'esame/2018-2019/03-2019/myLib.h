#ifndef myLib_h
#define myLib_h
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <TCanvas.h>
#include <TH1F.h>
#include <fstream>
#include <TStyle.h>
#include <TApplication.h>
#include <TH1D.h>
#include <TF1.h>

double rand_range (double xMin, double xMax);

double rand_media (double xMin, double xMax, int tries);

double rand_varianza (double xMin, double xMax, int tries);

double rand_dvz_std (double xMin, double xMax, int tries);

void isto_bin100_G (double xMin, double xMax, int tries);

void isto_bin100_C (double xMin, double xMax, double yMin, double yMax, int tries);

void isto_bin100_Exp (double xMin, double xMax, double mu, int tries);

double f_Cauchy (double x);

double f_Gaus (double x);

double f_Exp (double x, double mu);

double rand_TAC_G (double xMin, double xMax, double yMin, double yMax);

double rand_TAC_C (double xMin, double xMax, double yMin, double yMax);

double rand_FCI_Exp (double xMin, double xMax, double mu);

double fGaus (double x, double mu, double sigma);

double rand_TAC_Gaus (double mu, double sigma);

bool HitMiss_Gaus(double xMin, double xMax, double yMin, double yMax, double mu, double sigma);

double Area (double a, double b, double c,double d);

double Integral_HM (int nHit, int N, double Area);

double p_HM (int nHit, int N);

double Var_HM (double Area, double p, int N);

double StdVar_HM (double Var);

double myGauss (double* x, double* par);

double myParabola (double* x, double* par);

double myExp (double* x, double* par);

double sum (double* x, double* par);

bool ReadData(char* fileName, TH1D* myHisto);

void ComputeChi2(TH1D* myHisto, TF1* myFun, double& chi2, double& NDF);

//double rand_FCI_Exp (double mu);

#endif
