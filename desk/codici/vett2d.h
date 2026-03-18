#ifndef vett2d_h
#define vett2d_h

class vett2d {

	public:
	
	//default ctor
	vett2d();
	
	//ctor
	vett2d(double x, double y);
	
	//copy ctor
	vett2d(const vett2d &original);
	
	//operatori
	vett2d & operator= (const vett2d & original);
	vett2d operator+ (const vett2d & vec2);
	vett2d operator- (const vett2d & vec2);
	double operator* (const vett2d & vec1); //prodotto scalare tra due vettori
	double operator^ (const vett2d & vec1); //prodotto vettoriale (restituisce solo il 									modulo)
	
	//Metodi
	vett2d scalar_prod (double k); // prodotto di un vettore per uno scalare
	double mod();
	void print();
	void norm(); // normalizza a 1 il vettore
	double getx();
	double gety();	
	
	private:
	double x_p;
	double y_p;
};

#endif
