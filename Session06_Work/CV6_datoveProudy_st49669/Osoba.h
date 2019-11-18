#ifndef _OSOBA_H
#define _OSOBA_H
#include "Adresa.h"
#include "Datum.h"
#include <string>

using namespace std;

class Osoba
{
private:
	string _jmeno;
	string _prijmeni;
	Adresa _trvaleBydliste;
	Datum _datumNarozeni;

public:
	
	Osoba(string jmeno, string prijmeni, Adresa trvaleBydliste, Datum datumNarozeni);
	Osoba(){};
	~Osoba();
	friend std::ostream& operator<<(std::ostream &out, Osoba &osoba);
	friend std::istream& operator>>(std::istream &inp, Osoba &osoba);
};

#endif
