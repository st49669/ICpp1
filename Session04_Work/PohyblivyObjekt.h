#ifndef _POHYBLIVYOBJEKT_H
#define _POHYBLIVYOBJEKT_H
#include "Objekt.h"


class PohyblivyObjekt :
	public Objekt
{
private:
	double uhelNatoceni;
public:
	PohyblivyObjekt(int id) : Objekt(id) {};
	double GetUhelNatoceni() const;
	void SetUhelNatoceni(double const uhelNatoceni) ;
};
#endif

