#ifndef data_h
#define data_h

class data {

	public:
		//costruttori
		data();
		data(int day, int month, int year);
		data(const data& other);

		//operator overloads
		data& operator=(const data& other);
		bool operator==(const data& other) const;
		bool operator<(const data& other) const;

		//object methods
		void stampa() const;
		void imposta(int day, int month, int year);

		bool valida() const;
		bool Bisestile() const;
		int diff_giorni(const data other) const; 
		const char* giorno_settimana() const; 

		// metodi gia' implementati nel file .h
		bool operator!=(const data& other) const { return !this->operator==(other); }
		bool operator>(const data& other) const { return other.operator<(*this); }
		bool operator<=(const data& other) const { return !this->operator>(other); }
		bool operator>=(const data& other) const { return !this->operator<(other); }

	private:
		//attributes
		int year_p, month_p, day_p;

};

#endif
