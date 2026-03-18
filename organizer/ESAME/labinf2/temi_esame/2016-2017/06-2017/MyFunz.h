#ifndef LAMIALIBRERIA_H
#define LAMIALIBRERIA_H

//prodotto potenza ed esponenziale
double dist1(double* x, double* par);
double dist2(double* x, double* par);
double dist3(double* x, double* par);

//gaussiana, parabola e somma gaussiana e parabola
double myGauss(double* x, double* par);
double gauss_parabola(double* x, double* par);
double myParabola(double* x, double* par);

//esponenziale e somma due gaussiane e un esponenziale 
double myExp(double* x, double* par);
double sum(double* x, double* par);

#endif	//LAMIALIBRERIA_H

