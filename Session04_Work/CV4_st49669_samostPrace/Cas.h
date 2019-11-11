#ifndef _CAS_H
#define _CAS_H

#include "IComparable.h"

class Cas : public IComparable {
private:
	int hodiny = 12;
	int minuty = 0;
	int sekundy = 0;

public:
	Cas(int hod, int min, int sec);

	virtual ~Cas();

	int CompareTo(IComparable* obj) const;

	std::string ToString() const override;

};

#endif

