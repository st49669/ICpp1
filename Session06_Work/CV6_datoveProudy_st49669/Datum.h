#ifndef _DATUM_H
#define _DATUM_H

#include <istream>
#include <ostream>
#include <iostream>

struct Datum
{
private:
	int _den, _mesic, _rok;
public:
	Datum(int den, int mesic, int rok);
	Datum() {};
	friend std::ostream &operator<<(std::ostream& os, Datum& datum);
	friend std::istream &operator>>(std::istream& is, Datum& datum);
};
#endif //_DATUM_H
