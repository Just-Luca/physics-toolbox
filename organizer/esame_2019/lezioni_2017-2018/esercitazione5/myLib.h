#ifndef LAMIALIBRERIA_H
#define LAMIALIBRERIA_H

double f_Cauchy(double x);
double f_Gaus (double x, double mu, double sigma);
double FCI(double x, double m);
bool HitMiss_gaus(double xMin, double xMax, double yMin, double yMax);
double MC_gaus(double xMin, double xMax);

double media(double numeri[], int N);
double media_puntatori(double* num, int n);
void MediaVarianza(double* numeri, int N, double& Media, double& Varianza);

void ordinaVettore(int* vettore, int dim);

double rand_CLT(double xMin, double xMax, int tries);
double rand_FCI_exp(double mu);
double rand_range(double min, double max);
double rand_TAC(double xMin, double xMax, double yMin, double yMax);
double rand_TAC_gaus (double mu, double sigma);

void riempimentoRandom(int* vettore, int dim);
void riempimentoRandom(double* vettore, int dim);

void riempiVettore(double* numeri, int N);

void stampaVettore(int* vettore, int dim);
void stampaVettore(double* vettore, int dim);

double varianza(double numeri[], double media, int N);


#endif	//LAMIALIBRERIA_H

