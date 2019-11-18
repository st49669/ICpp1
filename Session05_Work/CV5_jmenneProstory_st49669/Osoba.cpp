#include "stdafx.h"
#include "Osoba.h"


Entity::Osoba::Osoba(string jmeno, string telefon, int id)
{
	this->_jmeno = jmeno;
	this->_telefon = telefon;
	this->_id = id;
}

string Entity::Osoba::GetJmeno() const
{
	return _jmeno;
}

string Entity::Osoba::GetTelefon() const
{
	return _telefon;
}

int Entity::Osoba::GetId() const
{
	return _id;
}

string Entity::Osoba::ToString() const
{
	string ret = "{ID: " + to_string(_id);
	ret += "; jmeno: " + _jmeno;
	ret += "; telefon: " + _telefon;
	ret += ";}\n";
	return ret;
}
