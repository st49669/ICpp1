#include "stdafx.h"
#include "Hra.h"


#include <stdexcept>

/*int Hra::zjistiPocetStatObjektu()
{
	int pocetStatObj = 0;
	for (int i = 0; i < pocetVytvorenychObjektu; i++) {
		if (StatickyObjekt* t = dynamic_cast<StatickyObjekt*>(this->objekty[i])) {
			pocetStatObj++;
		}
	}
	return pocetStatObj;
}

int Hra::zjistiPocetPohObjektu()
{
	int pocetPohObj = 0;
	for (int i = 0; i < pocetVytvorenychObjektu; i++) {
		if (PohyblivyObjekt* t = dynamic_cast<PohyblivyObjekt*>(this->objekty[i])) {
			pocetPohObj++;
		}
	}
	return pocetPohObj;
}

int* Hra::zjistiIdStatObjektu()
{
	
	int * vsechnaId = nullptr;
	size_t nalezenoObjektu = 0;
	for (int i = 0; i < pocetVytvorenychObjektu; i++) {
		if (StatickyObjekt* t = dynamic_cast<StatickyObjekt*>(this->objekty[i])) {
			vlozHodnotuDoPoleUkazatelu(vsechnaId, nalezenoObjektu, this->objekty[i]->GetID());
			nalezenoObjektu++;
		}
	}
	return vsechnaId;
}

int* Hra::zjistiIdPohObjektu()
{
	int * vsechnaId = nullptr;	
	size_t nalezenoObjektu = 0;
	for (int i = 0; i < pocetVytvorenychObjektu; i++) {
		if (PohyblivyObjekt* t = dynamic_cast<PohyblivyObjekt*>(this->objekty[i])) {
			vlozHodnotuDoPoleUkazatelu(vsechnaId, nalezenoObjektu, this->objekty[i]->GetID());
			nalezenoObjektu++;
		}
	}
	return vsechnaId;

}*/

int * Hra::vlozHodnotuDoPoleUkazatelu(int* puvodniPole, size_t puvodniVelikost, int novaHodnota)
{
	int* novePole = new int[puvodniVelikost+1]; //nova alokace pro dalsi int v poli

	if (puvodniVelikost > 0) {
		memcpy(novePole, puvodniPole, (puvodniVelikost + 1) * sizeof(int)); //kopirovani puvodniho pole do noveho
	}
	delete[] puvodniPole;

	novePole[puvodniVelikost] = novaHodnota;

	return novePole;
}

Objekt** Hra::vlozObjektDoPoleObjektu(Objekt** puvodniObjekty, size_t puvodniVelikost, Objekt* novyObjekt)
{
	Objekt** novePole = new Objekt*[puvodniVelikost + 1]; //nova alokace pro dalsi objekt

	if (puvodniVelikost > 0) {
		memcpy(novePole, puvodniObjekty, (puvodniVelikost + 1) * sizeof(Objekt*)); //kopirovani puvodniho pole do noveho
	}

	delete[] puvodniObjekty;
	novePole[puvodniVelikost] = novyObjekt;

	return novePole;
}

double Hra::vzdalenostObjektuOdBodu(double objX, double objY, double bodX, double bodY)
{
	return abs(sqrt((bodX - objX)*(bodX - objX) + (bodY - objY)*(bodY - objY)));
}

bool Hra::jeObjektMeziSouradnicemi(double objX, double objY, double xmin, double xmaxm, double ymin, double ymax)
{
	if (xmin >= xmaxm || ymin >= ymax) {
		throw std::invalid_argument("Definice rosahu oblasti pro hedani objektu je neplatna!");
		return false;
	}
	if ((xmin <= objX && objX <= xmaxm) && (ymin <= objY && objY <= ymax)) {
		return true;
	}
	return false;
}

bool Hra::jeNatocenObjektMeziUhly(double umin, double umax, double uobjekt)
{
	if (uobjekt <= umax && uobjekt >= umin) {
		return true;
	}
	return false;
}

void Hra::VlozObjekt(Objekt * o)
{
	if (pocetVytvorenychObjektu >= MAX_POCET_OBJEKTU) {
		throw std::length_error("Dosazen maximalni pocet objektu ve scene!");
	}
	else 
	{
		this->objekty[pocetVytvorenychObjektu] = o;
		pocetVytvorenychObjektu++;
	}
	
}

int * Hra::NajdiIdStatickychObjektu(double xmin, double xmaxm, double ymin, double ymax)
{
	int* idNalezenychStatObj = nullptr; //pule, ve kterem se vraci nalezena ID objektu
	size_t nalezenychStatObj = 0; //kolik stat. objektu je pridano do nalezenych ID objektu

	for (int i = 0; i < pocetVytvorenychObjektu; i++)
	{
		if (dynamic_cast<StatickyObjekt*>(this->objekty[i]) != nullptr) //hledani stat. objektu mezi vsemi objekty
		{
			bool objektMeziSourad = jeObjektMeziSouradnicemi(objekty[i]->GetX(), objekty[i]->GetY(),
				xmin, xmaxm, ymin, ymax); //kontrola, jestli stat. objekt je v oblasti
			if (objektMeziSourad) { //zaradit mezi objekty v oblasti
				idNalezenychStatObj = vlozHodnotuDoPoleUkazatelu(idNalezenychStatObj, nalezenychStatObj, this->objekty[i]->GetID());
				nalezenychStatObj++; //nalezen dalsi objekt v oblasti
			}
		}
	}
	this->NalezenoStatickychObjektu = nalezenychStatObj;
	return idNalezenychStatObj;
	
}

PohyblivyObjekt ** Hra::NajdiPohybliveObjektyVOblasti(double x, double y, double r)
{
	PohyblivyObjekt** nalezenePohObjekty = nullptr; //pole, ve kterem se vraci nalezena ID objektu
	size_t nalezenychPohObj = 0; //kolik stat. objektu je pridano do nalezenych ID objektu

	for (int i = 0; i < pocetVytvorenychObjektu; i++)
	{
		if (dynamic_cast<PohyblivyObjekt*>(this->objekty[i]) != nullptr) //hledani poh. objektu mezi vsemi objekty
		{
			int vzdalenostObjektu = vzdalenostObjektuOdBodu(this->objekty[i]->GetX(),
				this->objekty[i]->GetY(), x, y);//kontrola, jestli poh. objekt je v oblasti radiusu
			if (vzdalenostObjektu <= r) { //zaradit mezi objekty v oblasti radiusu
				nalezenePohObjekty = (PohyblivyObjekt**)vlozObjektDoPoleObjektu(
					(Objekt**)nalezenePohObjekty, nalezenychPohObj, this->objekty[i]); //vlozit nalezeny objekt do pole objektu
				nalezenychPohObj++; //nalezen dalsi objekt v oblasti
			}
		}
	}
	this->NalezenoPohyblivychObjektu = nalezenychPohObj;
	return nalezenePohObjekty;
}

PohyblivyObjekt ** Hra::NajdiPohybliveObjektyVOblasti(double x, double y, double r, double umin, double umax)
{
	PohyblivyObjekt** nalezenePohObjekty = nullptr; //pole, ve kterem se vraci nalezena ID objektu
	size_t nalezenychPohObj = 0; //kolik stat. objektu je pridano do nalezenych ID objektu

	for (int i = 0; i < pocetVytvorenychObjektu; i++)
	{
		if (dynamic_cast<PohyblivyObjekt*>(this->objekty[i]) != nullptr) //hledani poh. objektu mezi vsemi objekty
		{
			int vzdalenostObjektu = vzdalenostObjektuOdBodu(this->objekty[i]->GetX(),
				this->objekty[i]->GetY(), x, y);//kontrola, jestli poh. objekt je v oblasti radiusu

			if (vzdalenostObjektu <= r) { //podstoupit dalsi kontrole
				PohyblivyObjekt* curr = (PohyblivyObjekt*)this->objekty[i]; //pretypovani potreba pro pristup k metodam tridy PohyblivyObjekt
				if (jeNatocenObjektMeziUhly(umin, umax, curr->GetUhelNatoceni())) //kontrola mezi natoceni
				{
					nalezenePohObjekty = (PohyblivyObjekt**)vlozObjektDoPoleObjektu(
						(Objekt**)nalezenePohObjekty, nalezenychPohObj, this->objekty[i]); //vlozit nalezeny objekt do pole objektu
					nalezenychPohObj++; //nalezen dalsi objekt v oblasti
				}
				
			}
		}
	}
	this->NalezenoPohyblivychObjektuSpravneOtocenych = nalezenychPohObj;

	return nalezenePohObjekty;
}
