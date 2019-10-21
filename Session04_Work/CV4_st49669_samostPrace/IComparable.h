

#ifndef _ICOMPARABLE_H
#define _ICOMPARABLE_H

#include "IObject.h"

#include <iostream>
#include <string>

class IComparable : IObject
{
public:
	virtual int compareTo(IComparable* obj) const;
	virtual string ToString() const;
};

#endif;

