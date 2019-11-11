#ifndef _DATUM_H
#define _DATUM_H

#include <istream>
#include <ostream>
#include <iostream>

struct Datum
{
private:
	int den, mesic, rok;
public:
	Datum(int den, int mesic, int rok);
	friend std::ostream &operator<<(std::ostream& os, Datum& datum);
	friend std::istream &operator>>(std::istream& is, Datum& datum);
};
#endif //_DATUM_H
