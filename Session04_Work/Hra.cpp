#include "stdafx.h"
#include "Hra.h"




void Hra::VlozObjekt(Objekt * o)
{
	if (pocetVytvorenychObjektu >= 100) {
		throw pocetVytvorenychObjektu;
	}
	else {
		this->objekty[pocetVytvorenychObjektu] = o;
		pocetVytvorenychObjektu++;
	}
	
}

int * Hra::NajdiIdStatickychObjektu(double xmin, double xmaxm, double ymin, double ymax)
{
	int pocetStatObj = 0;
	for (int i = 0; i < pocetVytvorenychObjektu; i++) {
		if (StatickyObjekt* t = dynamic_cast<StatickyObjekt*>(this->objekty[i])) {
			pocetStatObj++;
		}
	}

	
	if (pocetStatObj > 0) {
		int * vsechnaId = new int[pocetStatObj];
		int pozicePoleVsechnaId = 0;
		for (int i = 0; i < pocetVytvorenychObjektu; i++) {
			if (StatickyObjekt* t = dynamic_cast<StatickyObjekt*>(this->objekty[i])) {
				vsechnaId[pozicePoleVsechnaId] = this->objekty[i]->getID();
			}
		}
		return vsechnaId;
	}

	
	return nullptr;
	
}

PohyblivyObjekt ** Hra::NajdiPohybliveObjektyVOblasti(double x, double y, double r)
{
	//TODO: impelentace
	return nullptr;
}

PohyblivyObjekt ** Hra::NajdiPohybliveObjektyVOblasti(double x, double y, double r, double umin, double umax)
{
	//TODO: impelentace
	return nullptr;
}
