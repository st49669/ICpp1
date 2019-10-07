#include "stdafx.h"
#include "Pokladna.h"


int Pokladna::citacId = 1000;

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
	uc[pocetVydanychUctenek].setCastka(castka);
	uc[pocetVydanychUctenek].setCislo(citacId);
	uc[pocetVydanychUctenek].setDph(dph);
	pocetVydanychUctenek++;
	citacId++;
	return uc[pocetVydanychUctenek - 1];
}

Uctenka & Pokladna::dejUctenku(int id)
{
	for (int i = 0; i < pocetVydanychUctenek; i++) {
		if (uc[i].getCislo() == id) {
			return uc[i];
		}
	}
	return uc[0];
}


double Pokladna::dejCastku() const
{
	double castka = 0;
	for (int i = 0; i < pocetVydanychUctenek; i++) {
		castka += uc[i].getCastka();
	}
	return castka;
}

double Pokladna::dejCastkuVcDph() const
{
	double castka = 0;
	for (int i = 0; i < pocetVydanychUctenek; i++) {
		castka += uc[i].getCastka() * (1 + (uc[i].getDph() / 100));
	}
	return castka;
}
