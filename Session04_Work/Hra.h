#ifndef _HRA_H
#define _HRA_H
#include "Objekt.h"
#include "PohyblivyObjekt.h"


class Hra {

private:
	Objekt * * objekty;
public:
	Hra() {};
	void VlozObjekt(Objekt* o);
	int* NajdiIdStatickychObjektu(double xmin, double xmaxm, double ymin, double ymax);
	PohyblivyObjekt** NajdiPohybliveObjektyVOblasti(double x, double y, double r);
	PohyblivyObjekt** NajdiPohybliveObjektyVOblasti(double x, double y, double r, double umin, double umax);
};
#endif

