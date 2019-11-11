#ifndef _OSOBA_H
#define _OSOBA_H
#include "Adresa.h"
#include "Datum.h"
#include <string>

using namespace std;

class Osoba
{
private:
	string jmeno;
	string prijmeni;
	Adresa* trvaleBydliste;
	Datum* datumNarozeni;

public:
	Osoba(string jmeno, string prijmeni, Adresa* trvaleBydliste, Datum* datumNarozeni);
};

#endif
