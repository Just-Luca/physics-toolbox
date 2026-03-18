#ifndef LAMIALIBRERIA_H
#define LAMIALIBRERIA_H

double computeChi2(TH1F* myHisto, TF1* myFun);

double fun1(double* x, double* par);
double fun2(double* x, double* par);
double fun3(double* x, double* par);

bool readData(const std::string filename, std::vector<double>& vectNum);

#endif	//LAMIALIBRERIA_H

