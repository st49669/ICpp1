#ifndef _ADRESA_H
#define _ADRESA_H
#include <string>

using namespace std;

class Adresa
{
private:
	string _ulice;
	string _mesto;
	int _psc;
public:
	Adresa(string ulice, string mesto, int psc);
	Adresa() {};
	friend std::ostream &operator<<(std::ostream& os, Adresa& adresa);
	friend std::istream &operator>>(std::istream& is, Adresa& adresa);
};

#endif _ADRESA_H