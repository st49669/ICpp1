#ifndef __ITERATOR_H
#define __ITERATOR_H
#include "platform.h"
#include "Object.h"
#include "IntObject.h"
#include "StringObject.h"
#include "DoubleObject.h"
#include "FieldObject.h"

class DLL_SPEC Iterator {
public:
	virtual ~Iterator() {}

	// Posun na další øádek (vrací true, pokud je iterátor platnı; logika podle Java Iterator)
	virtual bool moveNext() = 0;
	// Vrací pole Object* obsahující data øádku
	virtual Object** getRow() = 0;
	// Vrací interní rowId aktuálního øádku
	virtual int getRowId() = 0;
	// Uzavøe iterátor (dealokuje pamìové prostøedky)
	virtual void close() = 0;
};
#endif

