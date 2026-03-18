#include <iostream>
#include "frazione.h"

frazione::frazione(const int numeratore, const int denominatore) {
	this->numeratore = numeratore;
	this->denominatore = denominatore;
}

frazione::frazione(const frazione& other) {
	numeratore = other.numeratore;
	denominatore = other.denominatore;
}

frazione::~frazione() {
	// do noting
}

frazione& frazione::operator=(const frazione& other) {
	numeratore = other.numeratore;
	denominatore = other.denominatore;
	return *this;	
}

int frazione::compara(const frazione& other) {
	double fraz1 = (double) numeratore / denominatore;
	double fraz2 = (double) other.numeratore / other.denominatore;

	if (fraz1 > fraz2) {
		return 1;
	}
	else if (fraz1 < fraz2) {
		return -1;
	}
	else {
		return 0;
	}
}

void frazione::somma(const frazione& other) {
	numeratore = numeratore * other.denominatore + other.numeratore * denominatore;
	denominatore = denominatore * other.denominatore;
	semplifica();
}

void frazione::sottrai(const frazione& other) {
	numeratore = numeratore * other.denominatore - other.numeratore * denominatore;
	denominatore = denominatore * other.denominatore;
	semplifica();
}

void frazione::moltiplica(const frazione& other) {
	numeratore *= other.numeratore;
	denominatore *= other.denominatore;
	semplifica();
}

void frazione::dividi(const frazione& other) {
	numeratore *= other.denominatore;
	denominatore *= other.numeratore;
	semplifica();
}

void frazione::semplifica() {
	int minimo = (numeratore > denominatore) ? denominatore : numeratore;

	int mcd = 0;
	for (int i = 2; i <= minimo; ++i) {
		if (numeratore % i == 0 && denominatore % i == 0) {
			mcd = i;
		}
	}

	if (mcd != 0) {
		numeratore /= mcd;
		denominatore /= mcd;
	}
}

void frazione::stampa() const {
	cout << numeratore << " / " << denominatore << endl;
}
