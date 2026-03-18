//Questo programma realizza una funzione che risolve un'equazione di secondo grado

#include <iostream>
#include <cmath>

bool solve2ndDegree(double* par, double* x)
{
	double delta;
	delta = pow(par[1], 2) - 4*par[0]*par[2];
	
	if(delta >= 0)
	{
		x[0] = (-par[1] + sqrt(delta))/(2*par[0]);
		x[1] = (-par[1] - sqrt(delta))/(2*par[0]);
		return x;
	}
}

void stampaSoluzioni(double* x)
{
	std::cout << "Le soluzioni sono:" << std::endl;
	for(int i = 0; i < 2; i++)
		std::cout << "x" << i+1 << " = " << x[i] << std::endl;
} 

/*****MAIN*****/

int main ()
{
	double par[3];
	double x[2];
	
	std::cout << "Inserire i coefficienti dell'equazione: " << std::endl;
	std::cout << "a = ";
	std::cin >> par[0];
	std:: cout << "b = ";
	std::cin >> par[1];
	std::cout << "c = ";
	std::cin >> par[2];
	
	if(solve2ndDegree(par, x))
		stampaSoluzioni(x);
	else
		std::cout << "L'equazione non ha soluzioni reali" << std::endl;

	return 0;		
}
