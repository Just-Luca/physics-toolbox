#ifndef misura_h
#define misura_h
 
#include <string>
 
using namespace std;
 
class misura {
 
 public:
  misura();
  misura(const string& filename);
  ~misura();
  
  void Somma (const misura& other);
  void SommaCorr (const misura& other, const double &cov);
  void Moltiplica (const misura& other);
  void Confronta (const misura& other) const;

  //implemento due metodi per accedere ai valori delle variabili private della
  //classe
  double GetX() const {return X_p;}
  double GetEX() const{return EX_p;}
  
 private:
  double X_p;
  double EX_p;
 
};
 
#endif
