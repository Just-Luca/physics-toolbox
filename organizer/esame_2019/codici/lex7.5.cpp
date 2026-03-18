#include <cmath>	
#include <cstdlib>
#include "complesso.h"
#include <iostream>
#include <vector>

using namespace std;

int main () {

	double a;
	double b;
	
	vector<complesso> N_complessi;
	
	cout << "Inserisci i numeri complessi (Re e Im): " << endl;
	
	while (a != 0 || b != 0) {  
		
		cin >> a >> b;
		
		complesso z(a, b);
		
		N_complessi.push_back(z);
	}
	
	cout << "" << endl;

	for (int i = 0; i < N_complessi.size() - 1; i++) {
		
		cout << i + 1 << ") ";
		N_complessi[i].Print();
	}
	
	cout << "" << endl;
	
	cout <<"Hai inserito " << N_complessi.size() - 1 << " numeri complessi." << endl;
	
	complesso somma(0., 0.);
	
	for (int r = 0; r < N_complessi.size() - 1; ++r) {
	
		somma = somma + N_complessi[r];
	}
	
	cout << "" << endl;
	
	cout << "La somma dei complessi inseriti è: ";
	somma.Print();
	cout << endl;
	
	return 0;
}
