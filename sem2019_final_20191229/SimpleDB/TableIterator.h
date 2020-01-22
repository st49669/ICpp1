#pragma once
#include "Iterator.h"
class TableIterator : public Iterator
{
public:
	TableIterator(Object ***data, int rowsCount);
	virtual ~TableIterator();

	// Posun na další øádek (vrací true, pokud je iterátor platnı; logika podle Java Iterator)
	virtual bool moveNext() override;
	// Vrací pole Object* obsahující data øádku
	virtual Object** getRow() override;
	// Vrací interní rowId aktuálního øádku
	virtual int getRowId() override;
	// Uzavøe iterátor (dealokuje pamìové prostøedky)
	virtual void close() override;

private:
	Object ***data;
	int iterPos = 0;
	int dataRowsTotal = 0;
};

