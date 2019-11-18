#include "stdafx.h"
#include "TelefonniSeznam.h"
#include <stdexcept>

Model::TelefonniSeznam::SpojovySeznam::SpojovySeznam(Entity::Osoba osoba)
{
	this->data = osoba;
	this->dalsi = nullptr;
}


Model::TelefonniSeznam::~TelefonniSeznam()
{
	while (_prvni != nullptr) {
		SpojovySeznam *pred = _prvni;
		_prvni = _prvni->dalsi;
		delete pred;
	}
}

string Model::TelefonniSeznam::NajdiCislo(string jmeno) const
{
	if (jmeno.empty()) //ze zadani - vyjimka pri prazdnem retezci
	{
		throw invalid_argument("Nebyl zadan retezec k hledani.");
	}
	SpojovySeznam *aktualni = _prvni;
	if (jmeno == aktualni->data.GetJmeno()) return aktualni->data.GetTelefon(); //pro pripad, kdyby v seznamu byl jen jeden prvek
	while (aktualni->dalsi != nullptr) {
		aktualni = aktualni->dalsi;
		if (jmeno == aktualni->data.GetJmeno()) return aktualni->data.GetTelefon();
	} 
	throw logic_error("Zadany retezec nebyl nalezen.");
}

string Model::TelefonniSeznam::NajdiCislo(int id) const
{
	if (id < 0) throw invalid_argument("Hledane ID nesmi byt zaporne.");
	SpojovySeznam *aktualni = _prvni;
	if (aktualni->data.GetId() == id) return aktualni->data.GetTelefon(); //pro pripad, kdyby v seznamu byl jen jeden prvek
	while (aktualni->dalsi != nullptr){
		aktualni = aktualni->dalsi;
		if (aktualni->data.GetId() == id) return aktualni->data.GetTelefon();
	} 
	throw logic_error("Zadane ID nebylo nalezeno.");
}

void Model::TelefonniSeznam::PridejOsobu(Entity::Osoba osoba)
{
	SpojovySeznam *doc = new SpojovySeznam(osoba);
	if (_prvni == nullptr) { //pridani 1. prvku
		_prvni = doc;
	}
	else {
		SpojovySeznam* doc2 = _prvni; //prohledavani od zacatku
		while (doc2->dalsi != nullptr) { //neznam aktualini pozici v seznamu, musim se tam dostat
			doc2 = doc2->dalsi;
		}
		doc2->dalsi = doc;
	}
	

}

string Model::TelefonniSeznam::ToString() const
{
	string ret ;
	if (_prvni != nullptr) {
		SpojovySeznam *aktualni = _prvni;
		do {
			ret += aktualni->data.ToString();
			aktualni = aktualni->dalsi;
		} while (aktualni != nullptr);

	}
	else {
		ret = "Seznam je prazdny.\n";
	}
	return ret;
}


