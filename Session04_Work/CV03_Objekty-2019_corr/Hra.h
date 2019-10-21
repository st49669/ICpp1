#ifndef _HRA_H
#define _HRA_H
#include "Objekt.h"
#include "PohyblivyObjekt.h"
#include "StatickyObjekt.h"

#define MAX_POCET_OBJEKTU 1000


class Hra {

private:
	Objekt ** objekty = new Objekt*[MAX_POCET_OBJEKTU];
	int pocetVytvorenychObjektu = 0;
	//int zjistiPocetStatObjektu();
	//int zjistiPocetPohObjektu();
	//int* zjistiIdStatObjektu();
	//int* zjistiIdPohObjektu();
	int* vlozHodnotuDoPoleUkazatelu(int* puvodniPole, size_t puvodniVelikost, int novaHodnota);
	Objekt ** vlozObjektDoPoleObjektu(Objekt** puvodniObjekty, size_t puvodniVelikost, Objekt* novyObjekt);
	double vzdalenostObjektuOdBodu(double objX, double objY, double bodX, double bodY);
	bool jeObjektMeziSouradnicemi(double objX, double objY, double xmin, double xmaxm, double ymin, double ymax);
	bool jeNatocenObjektMeziUhly(double umin, double umax, double uobjekt);
public:
	int NalezenoStatickychObjektu = 0; //pro ucely testovani v Main
	int NalezenoPohyblivychObjektu = 0; //pro ucely testovani v Main
	int NalezenoPohyblivychObjektuSpravneOtocenych = 0; //pro ucely testovani v Main
	Hra() {};
	~Hra() { delete[] objekty; };
	void VlozObjekt(Objekt* o);
	int* NajdiIdStatickychObjektu(double xmin, double xmaxm, double ymin, double ymax);
	PohyblivyObjekt** NajdiPohybliveObjektyVOblasti(double x, double y, double r);
	PohyblivyObjekt** NajdiPohybliveObjektyVOblasti(double x, double y, double r, double umin, double umax);
};
#endif

