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
	void SetCisloUctenky(int cisloUcctenky);
	void SetCastka(double castka);
	void SetDph(double dph);

	double GetDph();
	int GetCisloUctenky();
	double GetCastka();
};


#endif
