#include "stdafx.h"
#include "Uctenka.h"


void Uctenka::SetCisloUctenky(int cislo) {
	this->cisloUctenky = cislo;
}
void Uctenka::SetCastka(double castka) {
	this->castka = castka;
}
void Uctenka::SetDph(double dph) {
	this->dph = dph;
}

double Uctenka::GetDph() {
	return this->dph;
}
int Uctenka::GetCisloUctenky() {
	return this->cisloUctenky;
}
double Uctenka::GetCastka() {
	return this->castka;
}


