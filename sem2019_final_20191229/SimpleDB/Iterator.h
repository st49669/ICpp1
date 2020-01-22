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

	// Posun na dal�� ��dek (vrac� true, pokud je iter�tor platn�; logika podle Java Iterator)
	virtual bool moveNext() = 0;
	// Vrac� pole Object* obsahuj�c� data ��dku
	virtual Object** getRow() = 0;
	// Vrac� intern� rowId aktu�ln�ho ��dku
	virtual int getRowId() = 0;
	// Uzav�e iter�tor (dealokuje pam�ov� prost�edky)
	virtual void close() = 0;
};
#endif

