#ifndef _ADRESA_H
#define _ADRESA_H
#include <string>

using namespace std;

class Adresa
{
private:
	string ulice;
	string mesto;
	int psc;
public:
	Adresa(string ulice, string mesto, int psc);
};

#endif _ADRESA_H