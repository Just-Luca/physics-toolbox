#ifndef vett2d_h
#define vett2d_h

class vett2d
{
 public:
  // Default ctor
  vett2d ();
  
  // Ctor
  vett2d (double x, double y);
  
  // Copy ctor
  vett2d (const vett2d &original);
	
  // Operatori
  vett2d & operator= (const vett2d & original);
  vett2d operator+ (const vett2d & vec2);
  vett2d operator- (const vett2d & vec2);

  // Metodi
  vett2d scalar_prod (double k); // Moltiplicazione di un vettore per uno scalare
  double mod         ();         // Modulo del vettore
  void   print       ();
  void   norm        ();         // Metodo che rinormalizza il vettore a 1
  double getx        ();
  double gety        ();	
	
 private:
  double x_p;
  double y_p;
};

#endif
