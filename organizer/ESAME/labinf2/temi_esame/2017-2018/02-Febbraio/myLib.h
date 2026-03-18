#ifndef LAMIALIBRERIA_H
#define LAMIALIBRERIA_H

double ComputeChi2(TH1F* myHisto, TF1* myFun);

double f1(double* x, double* par);
double f2(double* x, double* par);

bool ReadData(char* fileName, TH1F* myHisto);

#endif	//LAMIALIBRERIA_H

