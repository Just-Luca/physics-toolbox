 #include <cstdlib>
 #include <ctime>
 #include <iostream>
 #include <cmath>
 
 #include "myLib.h"

 double rand_range(double min, double max) {
 	return min + (max - min) * rand() / (1. * RAND_MAX);
 }
 
 double fsin (double x) {
 	return 1.+sin(x);
 }

 bool HitMiss(double xMin, double xMax, 
 	      double yMin, double yMax) {
 	double x=0., y=0.;
	x = rand_range(xMin, xMax);
	y = rand_range(yMin, yMax);
	if (y < fsin(x)) return true;
	else return false;
 }
 




