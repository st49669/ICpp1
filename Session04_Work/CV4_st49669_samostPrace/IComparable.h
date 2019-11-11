

#ifndef _ICOMPARABLE_H
#define _ICOMPARABLE_H

#include "IObject.h"

#include <iostream>
#include <string>

class IComparable : public IObject
{
public:
	virtual int CompareTo(IComparable* obj) const = 0;
	virtual string ToString() const;
};

#endif

