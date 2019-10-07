#include "stdafx.h"
#include "Uctenka.h"


Uctenka::Uctenka()
{

}


Uctenka::~Uctenka()
{
}

void Uctenka::setCislo(int cislo) {
	this->cisloUctenky = cislo;
}
void Uctenka::setCastka(double castka) {
	this->castka = castka;
}
void Uctenka::setDph(double dph) {
	this->dph = dph;
}

double Uctenka::getDph() {
	return this->dph;
}
int Uctenka::getCislo() {
	return this->cisloUctenky;
}
double Uctenka::getCastka() {
	return this->castka;
}


