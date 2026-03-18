#include "complesso.h"
#include <iostream>
#include <iomanip>
#include <cmath>

//default constructor
complesso::complesso()
{
	//non mi serve definire un numero complesso (0, 0) perchè tutti gli attributi hanno già un costruttore di default
	//re_p = 0;
	//im_p = 0;
}

//constructor
complesso::complesso(const double& re, const double& im)
{
	re_p = re;
	im_p = im;
}

//copy constructor
complesso::complesso(const complesso& original)
{
	re_p = original.re_p;
	im_p = original.im_p;
}

//destructor
complesso::~complesso() {}

/*****************************************************************************************************************************/
//metodi
double complesso::Re() const
{
	return re_p;
}	

double complesso::Im() const
{
	return im_p;
}

double complesso::Mod() const
{ 
	return sqrt(re_p*re_p + im_p*im_p);
}

double complesso::Theta() const
{
	return atan(im_p/re_p);
}

double complesso::Rho() const
{
	return re_p*cos(Theta());
}

void complesso::Print() const
{
	std::cout << re_p << " + i" << Im() << std::endl;
} 

/**************************************************************************************************************************/
//operator
complesso& complesso::operator=(const complesso& original)
{
	re_p = original.Re();	//due metodi analoghi
	im_p = original.im_p;
	return *this;
}

complesso& complesso::operator=(const double& original)
{
	re_p = original;
	im_p = 0;
	return *this;
}

complesso complesso::operator+(const complesso& original)
{
	double re = re_p + original.re_p;
  	double im = im_p + original.im_p;
  
  	complesso rit(re, im);
  	return rit;
}

complesso complesso::operator-(const complesso& original)
{
	double re = re_p - original.re_p;
  	double im = im_p - original.im_p;
  
  	complesso rit(re, im);
  	return rit;
}

complesso complesso::operator*(const complesso& original)
{
	double re = re_p * original.re_p - im_p * original.im_p;
  	double im = im_p * original.re_p + re_p * original.im_p;
  
  	complesso rit(re, im);
  	return rit;
}

complesso complesso::operator/(const complesso& original)
{
  	double coeff = pow(original.re_p, 2) + pow(original.im_p, 2);
  	double re = (re_p * original.re_p + im_p * original.im_p) / coeff;
  	double im = (original.re_p * im_p - re_p * original.im_p) / coeff;
  
  	complesso rit(re, im);
  	return rit;
}

complesso complesso::operator^(const int& potenza)
{
  	complesso c(re_p, im_p);
  	for (int i = 1; i < potenza; i++)
		c = c*c;
    
  	return c;
}
