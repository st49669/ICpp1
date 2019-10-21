#include "stdafx.h"
#include "PohyblivyObjekt.h"

#include <stdexcept>




double PohyblivyObjekt::GetUhelNatoceni() const
{
	return this->uhelNatoceni;
}

void PohyblivyObjekt::SetUhelNatoceni(double uhelNatoceni) 
{
	if (uhelNatoceni < 0 || uhelNatoceni > 2 * M_PI) {
		throw std::invalid_argument("Neplatna hodnota uhlu natoceni, nastavuji hodnotu 0...");
		this->uhelNatoceni = 0;
	}
	else 
	{
		this->uhelNatoceni = uhelNatoceni;
	}
}
