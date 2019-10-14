
#include "stdafx.h"

#include "Objekt.h"

Objekt::Objekt(int id)
{
	this->id = id;
}


double Objekt::getX() const
{
	return x;
}

double Objekt::getY() const
{
	return y;
}

void Objekt::setX(double x) 
{
	this->x = x;

}

void Objekt::setY(double  y)
{
	this->y = y;
}

double Objekt::getID() const
{
	return id;
}

