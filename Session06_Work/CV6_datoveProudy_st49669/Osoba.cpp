#include "stdafx.h"
#include "Osoba.h"
#include "Adresa.h"
#include "Datum.h"


Osoba::Osoba(string jmeno, string prijmeni, Adresa trvaleBydliste, Datum datumNarozeni)
{
	_jmeno = jmeno;
	_prijmeni = prijmeni;
	_trvaleBydliste = trvaleBydliste;
	_datumNarozeni = datumNarozeni;
}

Osoba::~Osoba()
{
	delete &_trvaleBydliste;
	delete &_datumNarozeni;
}

std::ostream & operator<<(std::ostream & out, Osoba & osoba)
{
	return out << osoba._jmeno << " " << osoba._prijmeni << " " << osoba._trvaleBydliste
		<< " " << osoba._datumNarozeni << " " << std::endl;
}


std::istream & operator>>(std::istream & inp, Osoba & osoba)
{
	/*std::string tmp;
	getline(inp, tmp);
	std::cout << tmp << endl;*/

	string jmeno, prijmeni, ulice, mesto;
	int den, mesic, rok, psc;

	inp >> jmeno;
	inp >> prijmeni;
	inp >> ulice;
	inp >> mesto;
	inp >> psc;
	inp >> den;
	inp >> mesic;
	inp >> rok;

	cout << jmeno <<" "<< prijmeni << " " << ulice << " " << mesto << " " <<
		psc << " " << den << " " << mesic << " " << rok <<endl;

	/*Adresa *adr = new Adresa(ulice, mesto, psc);
	Datum *dat = new Datum(den, mesic, rok);

	Osoba *os = new Osoba(jmeno, prijmeni, *adr,* dat);

	osoba = *os;
	delete os;
	delete adr;
	delete dat;*/

	return inp;
}


