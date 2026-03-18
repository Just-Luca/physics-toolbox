//Questo programma scrive sul terminale la radice quadrata di 2, il cubo di 2 e il seno di pigreco/4

#include <iostream>
#include <cmath>

#define PI 3.14159265

int main ()
{	
	double due = 2;
	double radice_due = sqrt(due);
	double cubo_due = pow(2, 3);	
	double seno_piquarti = sin(PI/4);	

	std::cout << "La radice quadrata di 2 è: " << radice_due << std::endl;
	std::cout << "Il cubo di 2 è: " << cubo_due << std::endl;
	std::cout << "Il seno di pigreco/4 è: " << seno_piquarti << std::endl;
}
