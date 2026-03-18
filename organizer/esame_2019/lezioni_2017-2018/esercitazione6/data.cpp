#include "data.h"
#include <iostream>
#include <iomanip>
#include <cmath>

//default constructor
data::data()
{
	//non mi serve definire un numero complesso (0, 0) perchè tutti gli attributi hanno già un costruttore di default
	//re_p = 0;
	//im_p = 0;
}

//constructor
data::data(int day, int month, int year)
{
	day_p = day;
	month_p = month;
	year_p = year;
}

//copy constructor
data::data(const data& other)
{
	day_p = other.day_p;
	month_p = other.month_p;
	year_p = other.year_p;
}

/***********************************************************************************************************************************/
//operatori
data& data::operator=(const data& other)
{
	day_p = other.day_p;
	month_p = other.month_p;
	year_p = other.year_p;
	return *this;
}

bool data::operator==(const data& other) const
{
	return year_p == other.year_p && month_p == other.month_p && day_p == other.day_p;
}

bool data::operator<(const data& other) const
{
	if (*this == other) return false;
	
	if (year_p > other.year_p) return false;
	if (year_p < other.year_p) return true;
	
	// se arrivo qui, year_p==other.year_p
	if (month_p > other.month_p) return false;
	if (month_p < other.month_p) return true;
	
	// se arrivo qui, anche il mese è lo stesso	
	if (day_p > other.day_p) return false;
	else return true;
}

/***********************************************************************************************************************************/
//metodi
void data::stampa() const
{
	std::cout << day_p << "/" << month_p << "/" << year_p << std::endl;
}

void data::imposta(int day, int month, int year)
{
	day_p = day;
	month_p = month;
	year_p = year;
}

bool data::valida() const
{
	int month_length[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if((year_p % 4 == 0 && year_p % 100 != 0) || year_p % 400 == 0)
		month_length[1] = 29;
	if (month_p <= 0 || month_p > 12) return false;
	if (day_p <= 0 || day_p > month_length[month_p-1]) return false;

	return true;
}

bool data::Bisestile() const
{
	if((year_p % 4 == 0 && year_p % 100 != 0) || year_p % 400 == 0)
		return true;
	else return false;
}

int data::diff_giorni(const data other) const
{
	int DayCounter = 0;
	data dataPre;
	data dataPost;
	
	//verifico quale delle due date è antecedente
	if(other == *this)
		return 0;
	else if(*this < other)
	{
		dataPre = (*this);
		dataPost = other;
	}
	else
	{
		dataPre = other;
		dataPost = (*this);
	}
	
	//conto i giorni trascorsi da dataPre fino al 31 dicembre di quell'anno
	if(dataPre.Bisestile() == true)
	{
		int month_length[] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		DayCounter += month_length [dataPre.month_p - 1] - dataPre.day_p;
		for (int i=dataPre.month_p; i < 12; i++) 
			DayCounter += month_length[i];		
	}
	else
	{
		int month_length[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		DayCounter += month_length [dataPre.month_p - 1] - dataPre.day_p;
		for (int i=dataPre.month_p; i < 12; i++) 
		DayCounter += month_length[i];			
	}
	
	//sommo tanti anni quanti sono di differenza tra il 1/01 appena successivo a dataPre e il 1/01 dell'anno di dataPost
	data dataTemp = dataPre;
	
	while (dataPost.year_p > dataTemp.year_p + 1)
	{
		dataTemp.imposta(1, 1, dataTemp.year_p + 1);
		if (dataTemp.Bisestile()==true) DayCounter += 366;
		else DayCounter+=365;			
	}
	
	//conto i giorni dal 1 gennaio fino a dataPost
	
	if (dataPost.Bisestile()==true)
	{	
		int month_length[] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		DayCounter += dataPost.day_p; 
		for (int i=0; i<dataPost.month_p - 1; i++) 
			DayCounter += month_length[i];		
	}
	else
	{	
		int month_length[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		DayCounter += dataPost.day_p; 
		for (int i=0; i<dataPost.month_p - 1; i++) 
		DayCounter += month_length[i];	
	}
	
	// caso in cui DataPre e DataPost siano nello stesso anno
	if (dataPre.year_p == dataPost.year_p)
	{
		if (dataPre.Bisestile()==true )
			DayCounter -= 366;
		else DayCounter -= 365;
	}

	return DayCounter;
}

const char* data::giorno_settimana() const
{
	const char* giorni[] = { "lunedì", "martedì", "mercoledì", "giovedì", "venerdì", "sabato", "domenica" };
	data Riferimento (25, 12, 2017); // è lunedì!
	
	int diff = diff_giorni(Riferimento);
	int index = diff % 7;
	
	if (Riferimento == *this)
		return giorni[0];
	else if(Riferimento > *this)
		return giorni[7 - index];
	else return giorni[index];
}


