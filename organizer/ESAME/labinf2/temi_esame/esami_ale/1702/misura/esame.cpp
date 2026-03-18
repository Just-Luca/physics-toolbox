#include <iostream>
#include <fstream>

#include "misura.h"

#include <cstdlib>


using namespace std;

int main (){
  misura c ("misura.txt");
  cout << c.GetX() << endl;
  cout << c.GetEX() << endl;

  //istanzio due oggetti misura con il default constructor
  cout << "Misura 1: " << endl;
  misura c1;
  cout << endl
       << "Misura 2: " << endl;
  misura ni;

  cout << "c : velocita` della luce da file misura.txt" << endl
       << "c1: velocita` della luce data" << endl
       << "ni: velocita` del neutrino" << endl
       <<"-----------------------------------------------------------------------"
       << endl;
  cout << "Compatibilita` tra c e c1" << endl;
  c.Confronta(c1);
  cout << "----------------------------------------------------------------------"
       << endl;
  cout << "Compatibilita` tra c1 e ni" << endl;
  c1.Confronta(ni);
  cout << "----------------------------------------------------------------------"
       << endl;
  cout << "Compatibilita` tra ni e c" << endl;
  ni.Confronta(c);
  cout << "----------------------------------------------------------------------"
       << endl; 
}
