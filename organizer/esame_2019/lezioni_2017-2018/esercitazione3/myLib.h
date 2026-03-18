#ifndef LAMIALIBRERIA_H
#define LAMIALIBRERIA_H

double f_Cauchy(double x);
double FCI(double x, double m);

double media(double* num, int n);
void MediaVarianza(double* numeri, int N, double& Media, double& Varianza);

void ordinaVettore(int* vettore, int dim);

double rand_FCI_exp(double mu);
double rand_range(double min, double max);
double rand_TAC(double xMin, double xMax, double yMin, double yMax);

void riempimentoRandom(int* vettore, int dim);
void riempimentoRandom(double* vettore, int dim);

void riempiVettore(double* numeri, int N);

void stampaVettore(int* vettore, int dim);
void stampaVettore(double* vettore, int dim);

#endif	//LAMIALIBRERIA_H

