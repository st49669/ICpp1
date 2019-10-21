#include "stdafx.h"
#include "Monstrum.h"

#include <stdexcept>

int Monstrum::GetHp() const
{
	return 0;
}

void Monstrum::SetHP(int hp)
{
	this->hp = hp;
}


int Monstrum::GetMaxHP() const
{
	return 0;
}

void Monstrum::SetMaxHP(int maxhp) 
{
	if (maxhp <= 0) {
		throw std::invalid_argument("Maximalni HP nemuze byt nizsi nez 0, nastavuji 100...");
		this->maxhp = 100;
	}
	else {
		this->maxhp = maxhp;
	}
	
}


