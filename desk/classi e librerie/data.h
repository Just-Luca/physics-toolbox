#ifndef data_h
#define data_h

class data {

	public:
	
		data();
		data(int day, int month, int year);
		data(const data& original);
		~data();
		data& operator=(const data& original);
		bool operator==(const data& original) const;
		bool operator<(const data& original) const;

		void Print() const;
		void Set(int day, int month, int year);

		bool Valida() const;
		bool Bisestile() const;
		//int Diff_giorni(const data& original) const; 
		//const char* giorno_settimana() const; 

		// metodi gia' implementati nel file .h
		bool operator!=(const data& original) const { return !this->operator==(original); }
		bool operator>(const data& original) const { return original.operator<(*this); }
		bool operator<=(const data& original) const { return !this->operator>(original); }
		bool operator>=(const data& original) const { return !this->operator<(original); }

	private:
	
		int year_p, month_p, day_p;

};

#endif
