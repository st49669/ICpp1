
#include "stdafx.h"

#include "Objekt.h"

Objekt::Objekt(int id)
{
	this->id = id;
}


double Objekt::GetX() const
{
	return x;
}

double Objekt::GetY() const
{
	return y;
}

void Objekt::SetX(double x) 
{
	this->x = x;

}

void Objekt::SetY(double  y)
{
	this->y = y;
}

double Objekt::GetID() const
{
	return id;
}

