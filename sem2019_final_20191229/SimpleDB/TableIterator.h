#pragma once
#include "Iterator.h"
class TableIterator : public Iterator
{
public:
	TableIterator(Object ***data, int rowsCount);
	virtual ~TableIterator();

	// Posun na dal�� ��dek (vrac� true, pokud je iter�tor platn�; logika podle Java Iterator)
	virtual bool moveNext() override;
	// Vrac� pole Object* obsahuj�c� data ��dku
	virtual Object** getRow() override;
	// Vrac� intern� rowId aktu�ln�ho ��dku
	virtual int getRowId() override;
	// Uzav�e iter�tor (dealokuje pam�ov� prost�edky)
	virtual void close() override;

private:
	Object ***data;
	int iterPos = 0;
	int dataRowsTotal = 0;
};

