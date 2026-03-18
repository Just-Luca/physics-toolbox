
#include <iostream>

//Indicazione del prototipo
double raddoppia(double input);


int main() {

	double valore_iniziale = 4;
	double valore_finale = raddoppia(valore_iniziale);
	std::cout << valore_iniziale
	          << " x 2 = "
	          << valore_finale << std::endl;

	return 0;
}

//Definizione della funzione
double raddoppia(double input) {
	return input * 2;
}




