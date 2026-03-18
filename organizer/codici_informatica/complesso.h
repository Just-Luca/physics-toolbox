#ifndef complesso_h
#define complesso_h

class complesso {
 
	public:
 
	// constructors
	complesso ();
	complesso (const double &re, const double &im);
	complesso (const complesso &original);
	~complesso (); // distruttore
  
	// operator overloads
	complesso& operator= (const complesso &original);
	complesso& operator= (const double &original);
	complesso operator+ (const complesso &original);	
	complesso operator- (const complesso &original);
	complesso operator* (const complesso &original);
	complesso operator/ (const complesso &original);
	complesso operator^ (const int &potenza);

	// object methods
	double Re() const;
	double Im() const;
	double Mod() const;
	double Theta() const;
	void Print() const;
  
	private:
	
	// attributes
	double re_p;
	double im_p;	
  
};

#endif
