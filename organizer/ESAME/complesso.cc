#include <cmath>	
#include <cstdlib>
#include "complesso.h"
#include <iostream>

//costruttore
complesso::complesso(const double &re, const double &im) {

	re_p = re;
	im_p = im;
	
}

//default
complesso::complesso() {

	re_p = 0;
	im_p = 0;
}

//copy
complesso::complesso(const complesso &original) {

	re_p = original.re_p;
	im_p = original.im_p;
}

//distruttore
complesso::~complesso() {
	
	/*double *re_p = new double;
	double *im_p = new double;
	delete re_p, im_p;*/

}

//metodi

double complesso::Re() const {

	return re_p;
}

double complesso::Im() const {

	return im_p;
}

double complesso::Mod() const {
	
	return sqrt((re_p*re_p)+(im_p*im_p));
}

double complesso::Theta() const {

	return atan(im_p/re_p);
}

void complesso::Print() const {

	std::cout //<< "Il numero complesso è: "
		    << re_p << " + i(" << im_p << ")."
		    << std::endl;
} 

//operatori

complesso& complesso::operator=(const complesso &original) {
	
	re_p = original.re_p;
	im_p = original.im_p;
	
	return *this;
}

complesso& complesso::operator=(const double &original) {

	re_p = original;
	im_p = 0;

	return *this;
}

complesso complesso::operator+(const complesso &original) {
	
	complesso somma(original);
	
	somma.re_p += re_p;	
	somma.im_p += im_p;
	
	return somma;
}	
	
complesso complesso::operator-(const complesso &original) {
	
	complesso diff(original);
	
	diff.re_p = re_p-diff.re_p;	
	diff.im_p = im_p-diff.im_p;
	
	return diff;
}	
	
complesso complesso::operator*(const complesso &original) {
	
	complesso mol(original);
	
	mol.re_p = (re_p*mol.re_p)-(im_p*mol.im_p);	
	mol.im_p = (re_p*mol.im_p)+(im_p*mol.re_p);
	
	return mol;
}		

complesso complesso::operator^(const int &potenza) {
	
	complesso pot;
	
	pot.re_p = pow(this->Mod(), potenza)*cos(this->Theta()*potenza);	
	pot.im_p = pow(this->Mod(), potenza)*sin(this->Theta()*potenza);
	
	return pot;
}	

complesso complesso::operator/(const complesso &original) {
	
	complesso rest(original);
	
	rest.re_p = (this->Mod()/rest.Mod())*cos(this->Theta()-rest.Theta());	
	rest.im_p = (this->Mod()/rest.Mod())*sin(this->Theta()-rest.Theta());
	
	return rest;
}		




























	
	
	
	
	
	
	
	
	
	
	
	
	



