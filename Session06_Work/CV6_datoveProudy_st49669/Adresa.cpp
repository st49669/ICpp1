#include "stdafx.h"
#include "Adresa.h"



Adresa::Adresa(string ulice, string mesto, int psc)
{
	_mesto = mesto;
	_psc = psc;
	_ulice = ulice;
}

std::ostream &operator<<(std::ostream &out, Adresa &adresa)
{
	out << adresa._ulice << " " << adresa._mesto << " " << adresa._psc;
	return out;
}

std::istream &operator>>(std::istream &inp, Adresa &adresa)
{
	int ulice, mesto, psc;

	inp >> ulice;
	inp >> mesto;
	inp >> psc;

	adresa._mesto = mesto;
	adresa._psc = psc;
	adresa._ulice = ulice;

	return inp;
}

