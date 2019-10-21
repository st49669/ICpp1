#ifndef _IOBJECT_H
#define _IOBJECT_H

#include <iostream>
#include <string>

using namespace std;

class IObject
{
public:
	virtual string ToString() const;
};

#endif;
