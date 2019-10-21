#ifndef _POKLADNA_H
#define _POKLADNA_H

#include "Uctenka.h"
class Pokladna
{
private:
	Uctenka * uc;
	int pocetVydanychUctenek;
	static int citacId;
public:
	Pokladna();
	~Pokladna();
	Uctenka& vystavUctenku(double castka, double dph);
	Uctenka& dejUctenku(int cisloUctenky);
	double dejCastku() const;
	double dejCastkuVcDph() const;
};
#endif;
