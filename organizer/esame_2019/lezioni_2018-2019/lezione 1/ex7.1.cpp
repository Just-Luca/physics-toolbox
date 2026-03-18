#include <iostream>
#include <cmath>

double Media (float array[], int N) {
	
	double sum = 0.;
	
	for (int i = 0; i < N; ++i) {
	
		sum += array[i];
	}
	
	return sum/N;
}
	
double Varianza (float array[], int N) {

	double sum = 0.;
	double sumSq = 0.;
	
	for (int i = 0; i < N; ++i) {
		
		sum += array[i];
		sumSq += array[i]*array[i];
	}
	
	return sumSq/N - (sum/N)*(sum/N);
}
	
int main() {

	int N = 10;
	
	int a, b, c, d, e, f, g, h, i, l;
	
	std::cout << "Inserire 10 numeri interi:" << std::endl;
	
	std::cout << "1) " ; 
	std::cin >> a;
	std::cout << "2) " ;
	std::cin >> b;
	std::cout << "3) " ;
	std::cin >> c;
	std::cout << "4) " ;
	std::cin >> d;
	std::cout << "5) " ;
	std::cin >> e;
	std::cout << "6) " ;
	std::cin >> f;
	std::cout << "7) " ;
	std::cin >> g;
	std::cout << "8) " ;
	std::cin >> h;
	std::cout << "9) " ;
	std::cin >> i;
	std::cout << "10) " ;
	std::cin >> l;
	
	float array[] = {a, b, c, d, e, f, g, h, i, l};
	
	std::cout << "La media dei numeri inseriti è: " << Media(array,N) << std::endl;
	std::cout << "La varianza dei numeri inseriti è: " << Varianza(array,N) << std::endl;
	
	return 0;
}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
