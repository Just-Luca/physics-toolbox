#include <cmath>	
#include <cstdlib>
#include "vett2d.h"
#include <iostream>

int main () {

	double x,y,a,b,c,d;
	a = 7.1;
	b = 2.6;
	c = 1.3;
	d = 3.2;
	
	vett2d vec1(a, b);
	vett2d vec2(c, d);
	vett2d vec3(x, y);
	
	vec3 = vec1 + vec2;
	
	std::cout << "X.somma = " << vec3.getx() << std::endl; 
	std::cout << "Y.somma = " << vec3.gety() << std::endl;
}
