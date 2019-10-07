#ifndef _UCTENKA_H
#define _UCTENKA_H

#include <iostream>
#include <string>
class Uctenka
{
private:
	int cisloUctenky;
	double castka;
	double dph;
public:
	Uctenka();
	~Uctenka();
	void setCislo(int);
	void setCastka(double);
	void setDph(double);

	double getDph();
	int getCislo();
	double getCastka();
};


#endif
