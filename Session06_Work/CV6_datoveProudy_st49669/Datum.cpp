#include "stdafx.h"
#include "Datum.h"
#include <stdexcept>


Datum::Datum(int den, int mesic, int rok)
{
	if ((den < 1 || den > 31) || (mesic < 1 || mesic > 12)) {
		this->den = 1;
		this->mesic = 1;
		throw std::invalid_argument("Zadany den nebo mesic je neplatny, nastavim 1. 1.");
	}
	else {
		this->den = den;
		this->mesic = mesic;
		this->rok = rok;
	}
}

std::ostream &operator<<(std::ostream &out, Datum &datum)
{
	out << datum.den << "\t" << datum.mesic << "\t" << datum.rok << std::endl;
	return out;
}

std::istream &operator>>(std::istream &inp, Datum &datum)
{
	inp >> datum.den;
	inp >> datum.mesic;
	inp >> datum.rok;
}
