#ifndef LAMIALIBRERIA_H
#define LAMIALIBRERIA_H

double computeChi2(TH1F* myHisto, TF1* myFun);
bool readData(const std::string filename, std::vector<double>& vectNum1, std::vector<double>& vectNum2, std::vector<double>& vectNum3);

#endif	//LAMIALIBRERIA_H

