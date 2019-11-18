#include "stdafx.h"
#include "Datum.h"
#include <stdexcept>


Datum::Datum(int den, int mesic, int rok)
{
	if ((den < 1 || den > 31) || (mesic < 1 || mesic > 12)) {
		this->_den = 1;
		this->_mesic = 1;
		this->_rok = rok;
		throw std::invalid_argument("Zadany den nebo mesic je neplatny, nastavim 1. 1.");
	}
	else {
		this->_den = den;
		this->_mesic = mesic;
		this->_rok = rok;
	}
}

std::ostream &operator<<(std::ostream &out, Datum &datum)
{
	out << datum._den << " " << datum._mesic << " " << datum._rok;
	return out;
}

std::istream &operator>>(std::istream &inp, Datum &datum)
{
	int den, mesic, rok;

	inp >> den;
	inp >> mesic;
	inp >> rok;

	datum._den = den;
	datum._mesic = mesic;
	datum._rok = rok;

	return inp;
}
