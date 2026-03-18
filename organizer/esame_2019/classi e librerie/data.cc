#include <cmath>	
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include "data.h"

//costruttore
data::data(int day, int month, int year) {

	day_p = day;
	month_p = month;
	year_p = year;
}

//default
data::data() {

	day_p = 0;
	month_p = 0;
	year_p = 0;
}

//copy
data::data(const data& original) {

	day_p = original.day_p;
	month_p = original.month_p;
	year_p = original.year_p;
}

//distruttore
data::~data() {
	
	int *day_p = new int;
	int *month_p = new int;
	int *year_p = new int;
	delete day_p, month_p, year_p;
}

//operatori

data& data::operator=(const data &original) {
	
	day_p = original.day_p;
	month_p = original.month_p;
	year_p = original.year_p;
		
	return *this;
}

bool data::operator==(const data &original) const {

	if (day_p == original.day_p) return true;
	
	if (month_p == original.month_p) return true;
	
	if (year_p == original.year_p) return true;
	
}	
	
bool data::operator<(const data &original) const {

	return original.operator>(*this);
	
}
	
//metodi

void data::Print() const {
	
	if (day_p < 10 || month_p < 10) {
	
		std::cout << "La data inserita è: " << std::setfill('0') << std::setw(2) << day_p << "/" << std::setfill('0') << std::setw(2) << month_p << "/" << year_p << std::endl;
	
	} else {
	
		std::cout << "La data inserita è: " << day_p << "/" << month_p << "/" << year_p << std::endl;
	}
}

void data::Set(int day, int month, int year) {
	
	std::cout << "Inserisci una data (GG/MM/AAAA):" << std::endl;
	std::cin >> day_p;
	std::cin >> month_p;
	std::cin >> year_p;
	
}

bool data::Bisestile() const {

	if (year_p%4 == 0 && year_p%100 != 0) return true;
	if (year_p%400 == 0) return true;
}

bool data::Valida() const {

	if (day_p <= 0 || day_p > 31) return false;
	if (month_p <= 0 || month_p > 12) return false;
	if (year_p <= 0) return false;
	if (month_p == 4 && day_p == 31) return false;
	if (month_p == 6 && day_p == 31) return false;
	if (month_p == 9 && day_p == 31) return false;
	if (month_p == 11 && day_p == 31) return false;
	if (month_p == 2 && data::Bisestile() == true && day_p > 29) return false;
	if (month_p == 2 && data::Bisestile() == false && day_p > 28) return false;
}

int data::Diff_giorni(const data& original) const {
	
	int giorno1, mese1, anno1, giorno2, mese2, anno2, diff;
	
	data data1(giorno1, mese1, anno1);
	data data2(giorno2, mese2, anno2);
	
	int diff0 = mod(anno1-anno2);	
	int annox = 0;
	int n = 0;

	for (int i = 0; i < diff0; i++) {

		annox = min(anno1, anno2) + i;

		if (annox.Bisestile() == true) {
			
			n += n;
		} else return n;
	}

	diff1 = diff0*365 + n; 

	if (anno1 > anno2) {

	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
