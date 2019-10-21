#ifndef _STATICKYOBJEKT_H
#define _STATICKYOBJEKT_H
#include "Objekt.h"
class StatickyObjekt :
	public Objekt
{
private:
	enum TypPrekazky typPrekazky;
public:
	StatickyObjekt(int id, TypPrekazky typPrekazky) : Objekt(id) { this->typPrekazky = typPrekazky; };
	//Bohuzel nevim, jak dat telo takoveho kostruktoru s volanim predka do cpp souboru, ale fungunje to...

	TypPrekazky GetTypPrekazky() const;
};





enum TypPrekazky {
	Skala, MalaRostlina, VelkaRostlina
};

#endif