#include "stdafx.h"
#include "Pokladna.h"


int Pokladna::citacId = 500;

Pokladna::Pokladna()
{
	
	this->uc = new Uctenka[10];
	pocetVydanychUctenek = 0;
}


Pokladna::~Pokladna()
{
	delete[] uc;
}

Uctenka & Pokladna::vystavUctenku(double castka, double dph)
{
	try {
		if (pocetVydanychUctenek < 10) {
			uc[pocetVydanychUctenek].SetCastka(castka);
			uc[pocetVydanychUctenek].SetCisloUctenky(citacId);
			uc[pocetVydanychUctenek].SetDph(dph);
			pocetVydanychUctenek++;
			citacId++;
			return uc[pocetVydanychUctenek - 1];
		}
		throw pocetVydanychUctenek;
	}
	catch (int pocetVydanychUctenek) {
		std::cout << "Nelze vytvorit dalsi uctenku, pokladna je plna!" << std::endl;
	}

}

Uctenka & Pokladna::dejUctenku(int id)
{
	try {
		for (int i = 0; i < pocetVydanychUctenek; i++) {
			if (uc[i].GetCisloUctenky() == id) {
				return uc[i];
			}
		}
		throw id;
	}
	catch (int id) {
		std::cout << "Vyjimka - zadane cislo uctenky nenalezeno: " << id << "." <<std::endl;
	}
}

double Pokladna::dejCastku() const
{
	double castka = 0;
	for (int i = 0; i < pocetVydanychUctenek; i++) {
		castka += uc[i].GetCastka();
	}
	return castka;
}

double Pokladna::dejCastkuVcDph() const
{
	double castka = 0;
	for (int i = 0; i < pocetVydanychUctenek; i++) {
		castka += uc[i].GetCastka() * (1 + (uc[i].GetDph() / 100));
	}
	return castka;
}
