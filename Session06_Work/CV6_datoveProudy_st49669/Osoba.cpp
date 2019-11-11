#include "stdafx.h"
#include "Osoba.h"





Osoba::Osoba(string jmeno, string prijmeni, Adresa * trvaleBydliste, Datum * datumNarozeni)
{
	this->jmeno = jmeno;
	this->prijmeni = prijmeni;
	this->trvaleBydliste = trvaleBydliste;
	this->datumNarozeni = datumNarozeni;
}

