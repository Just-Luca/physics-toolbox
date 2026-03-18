#include "vett2d.h"
#include <iostream>
#include <cmath>

using namespace std;

//default ctor
vett2d::vett2d()
{
	//cout<<"Default ctor\n";
	x_p = 0.;
	y_p = 0.;
}

//ctor
vett2d::vett2d(double x, double y)
{
	//cout<<"Ctor\n";
	x_p = x;
	y_p = y;
}

//copy ctor
vett2d::vett2d(const vett2d &original)
{
	//cout<<"Copy Ctor\n";
	x_p = original.x_p;
	y_p = original.y_p;	
}
	
//operatori
vett2d & vett2d::operator= (const vett2d & original)
{
	x_p = original.x_p;
	y_p = original.y_p;
	return *this;
}

vett2d vett2d::operator+ (const vett2d & vec2)
{
	double x = x_p + vec2.x_p;
	double y = y_p + vec2.y_p;
	vett2d sum (x,y);
	return sum;
}

vett2d vett2d::operator- (const vett2d & vec2)
{
	double x = x_p - vec2.x_p;
	double y = y_p - vec2.y_p;
	vett2d diff (x,y);
	return diff;
}
	
//Metodi
vett2d vett2d::scalar_prod (double k)
{
	double x = x_p * k;
	double y = y_p * k;
	vett2d result (x,y);
	return result;
}

double vett2d::operator* (const vett2d & vec1)
{	
	return (x_p*vec1.x_p+y_p*vec1.y_p);
}

double vett2d::operator^ (const vett2d & vec1)
{	
	return (x_p*vec1.y_p-y_p*vec1.x_p);
}

double vett2d::mod()
{
	return (sqrt((x_p * x_p) + (y_p * y_p)));
}

void vett2d::print()
{
	cout << "(" << x_p << "," << y_p << ")" << endl;
}

void vett2d::norm()
{
	double norma = sqrt((x_p * x_p) + (y_p * y_p));
	x_p = x_p / norma;
	y_p = y_p / norma;
}

double vett2d::getx()
{
	return x_p;
}

double vett2d::gety()
{
	return y_p;
}
